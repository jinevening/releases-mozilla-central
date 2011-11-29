/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * FormHistory
 *
 * Used to store values that have been entered into forms which may later
 * be used to automatically fill in the values when the form is visited again.
 *
 * search(terms, queryData, callback)
 *   Look up values that have been previously stored.
 *     terms - array of terms to return data for
 *     queryData - object that contains the query terms
 *       The query object contains properties for each search criteria to match, where the value
 *       of the property specifies the value that term must have. For example,
 *       { term1: value1, term2: value2 }
 *     callback - callback that is called when results are available or an error occurs.
 *       The callback is passed a result array containing each found entry. Each element in
 *       the array is an object containing a property for each search term specified by 'terms'.
 * count(terms, queryData, callback)
 *   Find the number of stored entries that match the given criteria.
 *     queryData - array of objects that indicate the query. See the search method for details.
 *     callback - callback that is called when results are available or an error occurs.
 *       The callback is passed the number of found entries.
 * update(changes, callback)
 *    Write data to form history storage.
 *      changes - an array of changes to be made. If only one change is to be made, it
 *                may be passed as an object rather than a one-element array.
 *        Each change object is of the form:
 *          { op: operation, term1: value1, term2: value2, ... }
 *        Valid operations are:
 *          add - add a new entry
 *          update - update an existing entry
 *          remove - remove an entry
 *          bump - update the last accessed time on an entry
 *        The terms specified allow matching of one or more specific entries. If no terms
 *        are specified then all entries are matched. This means that { op: "remove" } is
 *        used to remove all entries and clear the form history.
 *      callback - callback that is called when results have been stored.
 * getAutoCompeteResults(searchString, params, callback)
 *   Retrieve an array of form history values suitable for display in an autocomplete list.
 *   Returns an mozIStoragePendingStatement that can be used to cancel the operation if
 *   needed.
 *     searchString - the string to search for, typically the entered value of a textbox
 *     params - zero or more filter arguments:
 *       fieldname - form field name
 *       agedWeight
 *       bucketSize
 *       expiryDate
 *       maxTimeGroundings
 *       timeGroupingSize
 *       prefixWeight
 *       boundaryWeight
 *     callback - callback that is called with the array of results. Each result in the array
 *                is an object with four arguments:
 *                  text, textLowerCase, frecency, totalScore
 * schemaVersion
 *   This property holds the version of the database schema
 *
 * Terms:
 *  guid - entry identifier. For 'add', a guid will be generated.
 *  fieldname - form field name
 *  value - form value
 *  timesUsed - the number of times the entry has been accessed
 *  firstUsed - the time the the entry was first created
 *  lastUsed - the time the entry was last accessed
 *  firstUsedStart - search for entries created after or at this time
 *  firstUsedEnd - search for entries created before or at this time
 *  lastUsedStart - search for entries last accessed after or at this time
 *  lastUsedEnd - search for entries last accessed before or at this time
 *
 * In all of the above methods, the callback argument should be an object with an
 *  onSuccess(args) and onFailure(error) function.
 */

EXPORTED_SYMBOLS = [ "FormHistory" ];

const Cc = Components.classes;
const Ci = Components.interfaces;
const Cr = Components.results;

Components.utils.import("resource://gre/modules/XPCOMUtils.jsm");
Components.utils.import("resource://gre/modules/Services.jsm");

XPCOMUtils.defineLazyServiceGetter(this, "uuidService",
                                   "@mozilla.org/uuid-generator;1",
                                   "nsIUUIDGenerator");

const DB_SCHEMA_VERSION = 4;
const DAY_IN_MS  = 86400000; // 1 day in milliseconds
const NOOP = function noop() {};

let Prefs = {
  initialized: false,

  get debug() { this.ensureInitialized(); return this._debug; },
  get enabled() { this.ensureInitialized(); return this._enabled; },
  get expireDays() { this.ensureInitialized(); return this._expireDays; },

  ensureInitialized: function() {
    if (this.initialized)
      return;

    this.initialized = true;

    this._debug = Services.prefs.getBoolPref("browser.formfill.debug");
    this._enabled = Services.prefs.getBoolPref("browser.formfill.enable");
    this._expireDays = Services.prefs.getIntPref("browser.formfill.expire_days");
  }
};

function log(aMessage) {
  if (Prefs.debug) {
    Services.console.logStringMessage("FormHistory: " + aMessage);
  }
}

function sendNotification(aType, aData) {
  if (typeof aData == "string") {
    let strWrapper = Cc["@mozilla.org/supports-string;1"].
                     createInstance(Ci.nsISupportsString);
    strWrapper.data = aData;
    aData = strWrapper;
  }
  else if (typeof aData == "number") {
    let intWrapper = Cc["@mozilla.org/supports-PRInt64;1"].
                     createInstance(Ci.nsISupportsPRInt64);
    intWrapper.data = aData;
    aData = intWrapper;
  }
  else if (aData) {
    throw Components.Exception("Invalid type " + (typeof aType) + " passed to sendNotification",
                               Cr.NS_ERROR_ILLEGAL_VALUE);
  }

  Services.obs.notifyObservers(aData, "satchel-storage-changed", aType);
}

/**
 * Current database schema
 */

const dbSchema = {
  tables : {
    moz_formhistory : {
      "id"        : "INTEGER PRIMARY KEY",
      "fieldname" : "TEXT NOT NULL",
      "value"     : "TEXT NOT NULL",
      "timesUsed" : "INTEGER",
      "firstUsed" : "INTEGER",
      "lastUsed"  : "INTEGER",
      "guid"      : "TEXT",
    },
  },
  indices : {
    moz_formhistory_index : {
      table   : "moz_formhistory",
      columns : [ "fieldname" ]
    },
    moz_formhistory_lastused_index : {
      table   : "moz_formhistory",
      columns : [ "lastUsed" ]
    },
    moz_formhistory_guid_index : {
      table   : "moz_formhistory",
      columns : [ "guid" ]
    },
  }
};

/**
 * Validating and processing API querying data
 */

const validFields = [
  "fieldname",
  "value",
  "timesUsed",
  "firstUsed",
  "lastUsed",
  "guid",
];

const searchFilters = [
  "firstUsedStart",
  "firstUsedEnd",
  "lastUsedStart",
  "lastUsedEnd",
];

function validateOpData(aData, aDataType) {
  for (let field in aData) {
    if (field != "op" && validFields.indexOf(field) == -1) {
      throw Components.Exception(
        aDataType + " query contains an unrecognized field: " + field,
        Cr.NS_ERROR_ILLEGAL_VALUE);
    }
  }
  return aData;
}

function validateSearchData(aData, aDataType) {
  for (let field in aData) {
    if (field != "op" && validFields.indexOf(field) == -1 && searchFilters.indexOf(field) == -1) {
      throw Components.Exception(
        aDataType + " query contains an unrecognized field: " + field,
        Cr.NS_ERROR_ILLEGAL_VALUE);
    }
  }
}

function makeQueryPredicates(aQueryData, delimiter = ' AND ') {
  return Object.keys(aQueryData).map(function(field) {
    if (field == "firstUsedStart") {
      return "firstUsed >= :" + field;
    } else if (field == "firstUsedEnd") {
      return "firstUsed <= :" + field;
    } else if (field == "lastUsedStart") {
      return "lastUsed >= :" + field;
    } else if (field == "lastUsedEnd") {
      return "lastUsed <= :" + field;
    }
    return field + " = :" + field;
  }).join(delimiter);
}

/**
 * Storage statement creation and parameter binding
 */

function makeCountStatement(aSearchData) {
  let query = "SELECT COUNT(*) AS numEntries FROM moz_formhistory";
  let queryTerms = makeQueryPredicates(aSearchData);
  if (queryTerms) {
    query += " WHERE " + queryTerms;
  }
  return dbCreateAsyncStatement(query, aSearchData);
}

function makeSearchStatement(aSearchData, aSelectTerms) {
  let query = "SELECT " + aSelectTerms.join(", ") + " FROM moz_formhistory";
  let queryTerms = makeQueryPredicates(aSearchData);
  if (queryTerms) {
    query += " WHERE " + queryTerms;
  }

  return dbCreateAsyncStatement(query, aSearchData);
}

function makeAddStatement(aNewData, aNow, aBindingArrays) {
  let query = "INSERT INTO moz_formhistory (fieldname, value, timesUsed, firstUsed, lastUsed, guid) " +
              "VALUES (:fieldname, :value, :timesUsed, :firstUsed, :lastUsed, :guid)";

  aNewData.timesUsed = aNewData.timesUsed || 1;
  aNewData.firstUsed = aNewData.firstUsed || aNow;
  aNewData.lastUsed = aNewData.lastUsed || aNow;
  return dbCreateAsyncStatement(query, aNewData, aBindingArrays);
}

function makeBumpStatement(aGuid, aNow, aBindingArrays) {
  let query = "UPDATE moz_formhistory SET timesUsed = timesUsed + 1, lastUsed = :lastUsed WHERE guid = :guid";
  let queryParams = {
    lastUsed : aNow,
    guid : aGuid,
  };

  return dbCreateAsyncStatement(query, queryParams, aBindingArrays);
}

function makeRemoveStatement(aSearchData, aBindingArrays) {
  let query = "DELETE FROM moz_formhistory";
  let queryTerms = makeQueryPredicates(aSearchData);

  if (queryTerms) {
    log("removeEntries");
    query += " WHERE " + queryTerms;
  } else {
    log("removeAllEntries");
    // Not specifying any fields means we should remove all entries. We
    // won't need to modify the query in this case.
  }

  return dbCreateAsyncStatement(query, aSearchData, aBindingArrays);
}

function makeUpdateStatement(aGuid, aNewData, aBindingArrays) {
  let query = "UPDATE moz_formhistory SET ";
  let queryTerms = makeQueryPredicates(aNewData, ', ');

  if (!queryTerms) {
    throw Components.Exception("Update query must define fields to modify.",
                               Cr.NS_ERROR_ILLEGAL_VALUE);
  }

  query += queryTerms + " WHERE guid = :guid";
  aNewData["guid"] = aGuid;

  return dbCreateAsyncStatement(query, aNewData, aBindingArrays);
}

function generateGUID() {
  // string like: "{f60d9eac-9421-4abc-8491-8e8322b063d4}"
  let uuid = uuidService.generateUUID().toString();
  let raw = ""; // A string with the low bytes set to random values
  let bytes = 0;
  for (let i = 1; bytes < 12 ; i+= 2) {
    // Skip dashes
    if (uuid[i] == "-")
      i++;
    let hexVal = parseInt(uuid[i] + uuid[i + 1], 16);
    raw += String.fromCharCode(hexVal);
    bytes++;
  }
  return btoa(raw);
}

/**
 * Database creation and access
 */

let _dbConnection = null;
XPCOMUtils.defineLazyGetter(this, "dbConnection", function() {
  let dbFile;

  try {
    dbFile = Services.dirsvc.get("ProfD", Ci.nsIFile).clone();
    dbFile.append("formhistory.sqlite");
    log("Opening database at " + dbFile.path);

    _dbConnection = Services.storage.openUnsharedDatabase(dbFile);
    dbInit();
  } catch (e if e.result == Cr.NS_ERROR_FILE_CORRUPTED) {
    dbCleanup(dbFile);
    _dbConnection = Services.storage.openUnsharedDatabase(dbFile);
    dbInit();
  }

  return _dbConnection;
});


let dbStmts = new Map();

/*
 * dbCreateAsyncStatement
 *
 * Creates a statement, wraps it, and then does parameter replacement
 */
function dbCreateAsyncStatement(aQuery, aParams, aBindingArrays) {
  if (!aQuery)
    return null;

  let stmt = dbStmts.get(aQuery);
  if (!stmt) {
    log("Creating new statement for query: " + aQuery);
    stmt = dbConnection.createAsyncStatement(aQuery);
    dbStmts.set(aQuery, stmt);
  }

  if (aBindingArrays) {
    let bindingArray = aBindingArrays.get(stmt);
    if (!bindingArray) {
      // first time using a particular statement in update
      bindingArray = stmt.newBindingParamsArray();
      aBindingArrays.set(stmt, bindingArray);
    }

    if (aParams) {
      let bindingParams = bindingArray.newBindingParams();
      for (let field in aParams) {
        bindingParams.bindByName(field, aParams[field]);
      }
      bindingArray.addParams(bindingParams);
    }
  } else {
    if (aParams) {
      for (let field in aParams) {
        stmt.params[field] = aParams[field];
      }
    }
  }

  return stmt;
}

/**
 * dbInit
 *
 * Attempts to initialize the database. This creates the file if it doesn't
 * exist, performs any migrations, etc.
 */
function dbInit() {
  log("Initializing Database");

  if (!_dbConnection.tableExists("moz_formhistory")) {
    dbCreate();
    return;
  }

  // When FormHistory is released, we will no longer support the various schema versions prior to
  // this release that nsIFormHistory2 once did.
  let version = _dbConnection.schemaVersion;
  if (version < 3) {
    throw Components.Exception("DB version is unsupported.",
                               Cr.NS_ERROR_FILE_CORRUPTED);
  } else if (version != DB_SCHEMA_VERSION) {
    dbMigrate(version);
  }
}

function dbCreate() {
  log("Creating DB -- tables");
  for (let name in dbSchema.tables) {
    let table = dbSchema.tables[name];
    let tSQL = [[col, table[col]].join(" ") for (col in table)].join(", ");
    _dbConnection.createTable(name, tSQL);
  }

  log("Creating DB -- indices");
  for (let name in dbSchema.indices) {
    let index = dbSchema.indices[name];
    let statement = "CREATE INDEX IF NOT EXISTS " + name + " ON " + index.table +
                    "(" + index.columns.join(", ") + ")";
    _dbConnection.executeSimpleSQL(statement);
  }

  _dbConnection.schemaVersion = DB_SCHEMA_VERSION;
}

function dbMigrate(oldVersion) {
  log("Attempting to migrate from version " + oldVersion);

  if (oldVersion > DB_SCHEMA_VERSION) {
    log("Downgrading to version " + DB_SCHEMA_VERSION);
    // User's DB is newer. Sanity check that our expected columns are
    // present, and if so mark the lower version and merrily continue
    // on. If the columns are borked, something is wrong so blow away
    // the DB and start from scratch. [Future incompatible upgrades
    // should switch to a different table or file.]

    if (!dbAreExpectedColumnsPresent()) {
      throw Components.Exception("DB is missing expected columns",
                                 Cr.NS_ERROR_FILE_CORRUPTED);
    }

    // Change the stored version to the current version. If the user
    // runs the newer code again, it will see the lower version number
    // and re-upgrade (to fixup any entries the old code added).
    _dbConnection.schemaVersion = DB_SCHEMA_VERSION;
    return;
  }

  // Upgrade to newer version...
  let migrateStmts = [];
  for (let v = oldVersion + 1; v <= DB_SCHEMA_VERSION; v++) {
    log("Upgrading to version " + v + "...");
    let migrateFunction = "dbMigrateToVersion" + v;
    for each (let stmt in this[migrateFunction]()) {
      migrateStmts.push(stmt);
    }
  }

  _dbConnection.executeAsync(migrateStmts, migrateStmts.length, {
    handleResult : NOOP,
    handleError : function dbMigrateHandleError(aError) {
      throw Components.Exception(aError.message,
                                 Cr.NS_ERROR_UNEXPECTED);
    },
    handleCompletion : function dbMigrateHandleCompletion(aReason) {
      if (aReason == Ci.mozIStorageStatementCallback.REASON_FINISHED) {
        _dbConnection.schemaVersion = DB_SCHEMA_VERSION;
      }
    }
  });

  log("DB migration completed.");
}

// dbMigrateToVersion1 (bug 463154) -- unsupported as of Firefox 11
// dbMigrateToVersion2 (bug 243136) -- unsupported as of Firefox 11
// dbMigrateToVersion3 (bug 506402) -- unsupported as of Firefox 11

// WARNING: Newer dbMigrateToVersionXXX functions should return an
// ordered list of mozIStorageAsyncStatements (e.g. through
// dbCreateAsyncStatement) that modify and update the database rather than
// executing them from the function.

/**
 * dbAreExpectedColumnsPresent
 *
 * Sanity check to ensure that the columns this version of the code expects
 * are present in the DB we're using.
 */
function dbAreExpectedColumnsPresent() {
  for (let name in dbSchema.tables) {
    let table = dbSchema.tables[name];
    let query = "SELECT " +
                [col for (col in table)].join(", ") +
                " FROM " + name;
    try {
      let stmt = _dbConnection.createStatement(query);
      // (no need to execute statement, if it compiled we're good)
      stmt.finalize();
    } catch (e) {
      return false;
    }
  }

  log("verified that expected columns are present in DB.");
  return true;
}

/**
 * dbCleanup
 *
 * Called when database creation fails. Finalizes database statements,
 * closes the database connection, deletes the database file.
 */
function dbCleanup(dbFile) {
  log("Cleaning up DB file - close & remove & backup");

  // Create backup file
  let backupFile = dbFile.leafName + ".corrupt";
  Services.storage.backupDatabaseFile(dbFile, backupFile);

  dbClose(false);
  dbFile.remove(false);
}

function dbClose(aShutdown) {
  log("dbClose(" + aShutdown + ")");

  if (aShutdown) {
    sendNotification("formhistory-shutdown", null);
  }

  // Connection may never have been created if say open failed but we still
  // end up calling dbClose as part of the rest of dbCleanup.
  if (!_dbConnection) {
    return;
  }

  log("dbClose finalize statements");
  for (let stmt of dbStmts.values()) {
    stmt.finalize();
  }

  dbStmts = new Map();

  let closed = false;
  _dbConnection.asyncClose(function () closed = true);

  if (!aShutdown) {
    let thread = Services.tm.currentThread;
    while (!closed) {
      thread.processNextEvent(true);
    }
  }
}

/**
 * updateFormHistoryWrite
 *
 * Constructs and executes database statements from a pre-processed list of
 * inputted changes.
 */
function updateFormHistoryWrite(aChanges, aCallbacks) {
  log("updateFormHistoryWrite  " + aChanges.length);

  // pass 'now' down so that every entry in the batch has the same timestamp
  let now = Date.now() * 1000;

  // for each change, we either create and append a new storage statement to
  // stmts or bind a new set of parameters to an existing storage statement.
  // stmts and bindingArrays are updated when makeXXXStatement eventually
  // calls dbCreateAsyncStatement.
  let stmts = [];
  let notifications = [];
  let bindingArrays = new Map();

  for each (let change in aChanges) {
    let operation = change.op;
    delete change.op;
    let stmt;
    switch (operation) {
      case "remove":
        log("Remove from form history  " + change);
        stmt = makeRemoveStatement(change, bindingArrays);
        notifications.push([ "formhistory-remove", null ]);
        break;
      case "update":
        log("Update form history " + change);
        let guid = change.guid;
        delete change.guid;
        stmt = makeUpdateStatement(guid, change, bindingArrays);
        notifications.push([ "formhistory-update", guid ]);
        break;
      case "bump":
        log("Bump form history " + change);
        if (change.guid) {
          stmt = makeBumpStatement(change.guid, now, bindingArrays);
          notifications.push([ "formhistory-update", change.guid ]);
        } else {
          change.guid = generateGUID();
          stmt = makeAddStatement(change, now, bindingArrays);
          notifications.push([ "formhistory-add", change.guid ]);
        }
        break;
      case "add":
        log("Add to form history " + change);
        change.guid = generateGUID();
        stmt = makeAddStatement(change, now, bindingArrays);
        notifications.push([ "formhistory-add", change.guid ]);
        break;
      default:
        // We should've already guaranteed that change.op is one of the above
        throw Components.Exception("Invalid operation " + operation,
                                   Cr.NS_ERROR_ILLEGAL_VALUE);
    }

    // As identical statements are reused, only add statements if they aren't already present.
    if (stmt && stmts.indexOf(stmt) == -1) {
      stmts.push(stmt);
    }
  }

  for (let stmt of stmts) {
    stmt.bindParameters(bindingArrays.get(stmt));
  }

  let handlers = {
    handleCompletion : function updateFormHistoryCompletionHandler(aReason) {
      if (aReason == Ci.mozIStorageStatementCallback.REASON_FINISHED) {
        for (let [notification, param] of notifications) {
          // We're either sending a GUID or nothing at all.
          sendNotification(notification, param);
        }

        if (aCallbacks && aCallbacks.onSuccess) {
          aCallbacks.onSuccess();
        }
      }
    },
    handleError : function updateFormHistoryErrorHandler(aError) {
      if (aCallbacks && aCallbacks.onFailure) {
        aCallbacks.onFailure(aError);
      }
    },
    handleResult : NOOP
  };

  dbConnection.executeAsync(stmts, stmts.length, handlers);
}

/**
 * Functions that expire entries in form history and shrinks database
 * afterwards as necessary initiated by expireOldEntries.
 */

/**
 * expireOldEntriesDeletion
 *
 * Removes entries from database.
 */
function expireOldEntriesDeletion(aExpireTime, aBeginningCount) {
  log("expireOldEntriesDeletion(" + aExpireTime + "," + aBeginningCount + ")");

  FormHistory.update([
    {
      op: "remove",
      lastUsedEnd : aExpireTime,
    }], {
      onSuccess : function expireDeletionSuccess() {
        expireOldEntriesVacuum(aExpireTime, aBeginningCount);
      },
      onFailure : function expireDeletionFailure(aError) {
        log("expireOldEntriesDeletionFailure");
      }
  });
}

/**
 * expireOldEntriesVacuum
 *
 * Counts number of entries removed and shrinks database as necessary.
 */
function expireOldEntriesVacuum(aExpireTime, aBeginningCount) {
  FormHistory.count({}, {
    onSuccess : function expireEndCountSuccess(aEndingCount) {
      if (aBeginningCount - aEndingCount > 500) {
        log("expireOldEntriesVacuum");

        let stmt = dbCreateAsyncStatement("VACUUM");
        stmt.executeAsync({
          handleResult : NOOP,
          handleError : function expireVacuumErrorHandler(aError) {
            log("expireVacuumError");
          },
          handleCompletion : NOOP
        });
      }

      sendNotification("formhistory-expireoldentries", aExpireTime);
    },
    onFailure : function expireEndCountFailure(aError) {
      log("expireEndCountFailure");
    }
  });
}

const FormHistory = {
  search : function formHistorySearch(aSelectTerms, aSearchData, aCallbacks) {
    if (!aCallbacks || !aCallbacks.onSuccess) {
      throw Components.Exception("Search must define an onSuccess callback to receive results.",
                                 Cr.NS_ERROR_ILLEGAL_VALUE);
    }

    // if no terms selected, select everything
    aSelectTerms = (aSelectTerms) ?  aSelectTerms : validFields;
    validateSearchData(aSearchData, "Search");

    let stmt = makeSearchStatement(aSearchData, aSelectTerms);

    let handlers = {
      _results : [],

      handleResult : function searchResultHandler(aResultSet) {
        let formHistoryFields = dbSchema.tables.moz_formhistory;
        for (let row = aResultSet.getNextRow(); row; row = aResultSet.getNextRow()) {
          let result = {};
          for each (let field in aSelectTerms) {
            result[field] = row.getResultByName(field);
          }

          this._results.push(result);
        }
      },

      handleError : NOOP,

      handleCompletion : function searchCompletionHandler(aReason) {
        if (aReason == Ci.mozIStorageStatementCallback.REASON_FINISHED) {
          aCallbacks.onSuccess(this._results);
        }
      }
    };

    if (aCallbacks.onFailure) {
      handlers.handleError = function searchErrorHandler(aError) {
        aCallbacks.onFailure(aError);
      };
    }

    stmt.executeAsync(handlers);
  },

  count : function formHistoryCount(aSearchData, aCallbacks) {
    if (!aCallbacks || !aCallbacks.onSuccess) {
      throw Components.Exception("Count must define an onSuccess callback to receive results.",
                                 Cr.NS_ERROR_ILLEGAL_VALUE);
    }

    validateSearchData(aSearchData, "Count");
    let stmt = makeCountStatement(aSearchData);
    let handlers = {
      _count : null,
      handleResult : function countResultHandler(aResultSet) {
        let row = aResultSet.getNextRow();
        this._count = row.getResultByName("numEntries");
      },
      handleError : NOOP,
      handleCompletion : function countCompletionHandler(aReason) {
        if (aReason == Ci.mozIStorageStatementCallback.REASON_FINISHED) {
          aCallbacks.onSuccess(this._count);
        }
      }
    };

    if (aCallbacks.onFailure) {
      handlers.handleError = function countErrorHandler(aError) {
        aCallbacks.onFailure(aError);
      };
    }

    stmt.executeAsync(handlers);
  },

  update : function formHistoryUpdate(aChanges, aCallbacks) {
    if (!Prefs.enabled) {
      return;
    }

    // Used to keep track of how many searches have been started. When that number
    // are finished, updateFormHistoryWrite can be called.
    let searchHandler = {
      numSearches : 0,
      completedSearches : 0,
      failed : false
    };

    function validIdentifier(change) {
      // The identifier is only valid if one of either the guid or the (fieldname/value) are set
      return Boolean(change.guid) != Boolean(change.fieldname && change.value);
    }

    if (!("length" in aChanges))
      aChanges = [aChanges];

    for each (let change in aChanges) {
      switch (change.op) {
        case "remove":
          validateSearchData(change, "Remove");
          continue;
        case "update":
          if (validIdentifier(change)) {
            validateOpData(change, "Update");
            if (change.guid) {
              continue;
            }
          } else {
            throw Components.Exception(
              "update op='update' does not correctly reference a entry.",
              Cr.NS_ERROR_ILLEGAL_VALUE);
          }
          break;
        case "bump":
          if (validIdentifier(change)) {
            validateOpData(change, "Bump");
            if (change.guid) {
              continue;
            }
          } else {
            throw Components.Exception(
              "update op='bump' does not correctly reference a entry.",
              Cr.NS_ERROR_ILLEGAL_VALUE);
          }
          break;
        case "add":
          if (change.guid) {
            throw Components.Exception(
              "op='add' cannot contain field 'guid'. Either use op='update' " +
                "explicitly or make 'guid' undefined.",
              Cr.NS_ERROR_ILLEGAL_VALUE);
          } else if (change.fieldname && change.value) {
            validateOpData(change, "Add");
          }
          break;
        default:
          throw Components.Exception(
            "update does not recognize op='" + change.op + "'",
            Cr.NS_ERROR_ILLEGAL_VALUE);
      }

      searchHandler.numSearches++;
      FormHistory.search(
        [ "guid" ],
        {
          fieldname : change.fieldname,
          value : change.value
        }, {
          onSuccess : function updateFormHistoryPreprocessSuccess(aResults) {
            if (searchHandler.failed) {
              // We play cautiously and bail out if anything is wrong. The onFailure callback should
              // already have been called at this point.
              return;
            }

            if (aResults.length == 1) {
              change.guid = aResults[0]["guid"];
            } else if (aResults.length > 1) {
              log("Database contains multiple entries with the same fieldname/value pair.");
              if (aCallbacks && aCallbacks.onFailure) {
                aCallbacks.onFailure({
                  message :
                    "Database contains multiple entries with the same fieldname/value pair.",
                  result : 19 // Constraint violation
                });
              }

              searchHandler.failed = true;
              return;
            }

            searchHandler.completedSearches++;
            if (searchHandler.completedSearches == searchHandler.numSearches) {
              updateFormHistoryWrite(aChanges, aCallbacks);
            }
          },

          onFailure : function updateFormHistoryPreprocessFailure(aError) {
            log("updateFormHistoryPreprocessFailure");
            if (aCallbacks && aCallbacks.onFailure) {
              aCallbacks.onFailure(aError);
            }
          }
        });
    }

    if (searchHandler.numSearches == 0) {
      // We don't have to wait for any statements to return.
      updateFormHistoryWrite(aChanges, aCallbacks);
    }
  },

  getAutoCompleteResults: function getAutoCompleteResults(searchString, params, aCallback) {
    // only do substring matching when the search string contains more than one character
    let searchTokens;
    let where = ""
    let boundaryCalc = "";
    if (searchString.length > 1) {
        searchTokens = searchString.split(/\s+/);

        // build up the word boundary and prefix match bonus calculation
        boundaryCalc = "MAX(1, :prefixWeight * (value LIKE :valuePrefix ESCAPE '/') + (";
        // for each word, calculate word boundary weights for the SELECT clause and
        // add word to the WHERE clause of the query
        let tokenCalc = [];
        for (let i = 0; i < searchTokens.length; i++) {
            tokenCalc.push("(value LIKE :tokenBegin" + i + " ESCAPE '/') + " +
                            "(value LIKE :tokenBoundary" + i + " ESCAPE '/')");
            where += "AND (value LIKE :tokenContains" + i + " ESCAPE '/') ";
        }
        // add more weight if we have a traditional prefix match and
        // multiply boundary bonuses by boundary weight
        boundaryCalc += tokenCalc.join(" + ") + ") * :boundaryWeight)";
    } else if (searchString.length == 1) {
        where = "AND (value LIKE :valuePrefix ESCAPE '/') ";
        boundaryCalc = "1";
        delete params.prefixWeight;
        delete params.boundaryWeight;
    } else {
        where = "";
        boundaryCalc = "1";
        delete params.prefixWeight;
        delete params.boundaryWeight;
    }

    params.now = Date.now() * 1000; // convert from ms to microseconds

    /* Three factors in the frecency calculation for an entry (in order of use in calculation):
     * 1) average number of times used - items used more are ranked higher
     * 2) how recently it was last used - items used recently are ranked higher
     * 3) additional weight for aged entries surviving expiry - these entries are relevant
     *    since they have been used multiple times over a large time span so rank them higher
     * The score is then divided by the bucket size and we round the result so that entries
     * with a very similar frecency are bucketed together with an alphabetical sort. This is
     * to reduce the amount of moving around by entries while typing.
     */

    let query = "/* do not warn (bug 496471): can't use an index */ " +
                "SELECT value, " +
                "ROUND( " +
                    "timesUsed / MAX(1.0, (lastUsed - firstUsed) / :timeGroupingSize) * " +
                    "MAX(1.0, :maxTimeGroupings - (:now - lastUsed) / :timeGroupingSize) * "+
                    "MAX(1.0, :agedWeight * (firstUsed < :expiryDate)) / " +
                    ":bucketSize "+
                ", 3) AS frecency, " +
                boundaryCalc + " AS boundaryBonuses " +
                "FROM moz_formhistory " +
                "WHERE fieldname=:fieldname " + where +
                "ORDER BY ROUND(frecency * boundaryBonuses) DESC, UPPER(value) ASC";

    let stmt = dbCreateAsyncStatement(query, params);

    // Chicken and egg problem: Need the statement to escape the params we
    // pass to the function that gives us the statement. So, fix it up now.
    if (searchString.length >= 1)
      stmt.params.valuePrefix = stmt.escapeStringForLIKE(searchString, "/") + "%";
    if (searchString.length > 1) {
      for (let i = 0; i < searchTokens.length; i++) {
        let escapedToken = stmt.escapeStringForLIKE(searchTokens[i], "/");
        stmt.params["tokenBegin" + i] = escapedToken + "%";
        stmt.params["tokenBoundary" + i] =  "% " + escapedToken + "%";
        stmt.params["tokenContains" + i] = "%" + escapedToken + "%";
      }
    } else {
      // no additional params need to be substituted into the query when the
      // length is zero or one
    }

    let pending = stmt.executeAsync({
      _values : [],

      handleResult : function (aResultSet) {
          for (let row = aResultSet.getNextRow(); row; row = aResultSet.getNextRow()) {
              let value = row.getResultByName("value");
              let frecency = row.getResultByName("frecency");
              let entry = {
                  text :          value,
                  textLowerCase : value.toLowerCase(),
                  frecency :      frecency,
                  totalScore :    Math.round(frecency * row.getResultByName("boundaryBonuses"))
              };
              this._values.push(entry);
          }
      },

      handleError : function (aError) {
        aCallbacks(aError);
      },

      handleCompletion : function (aReason) {
        if (aReason == Ci.mozIStorageStatementCallback.REASON_FINISHED) {
          aCallback.onSuccess(this._values);
        }
      }
    });
    return pending;
  },

  get schemaVersion() {
    return dbConnection.schemaVersion;
  },

  // The remaining methods are called by FormHistoryStartup.js
  updatePrefs: function updatePrefs() {
    Prefs.initialized = false;
  },

  expireOldEntries: function expireOldEntries() {
    log("expireOldEntries");

    // Determine how many days of history we're supposed to keep.
    // Calculate expireTime in microseconds
    let expireTime = (Date.now() - Prefs.expireDays * DAY_IN_MS) * 1000;

    sendNotification("formhistory-beforeexpireoldentries", expireTime);

    FormHistory.count({}, {
      onSuccess : function expireStartCountSuccess(aBeginningCount) {
        expireOldEntriesDeletion(expireTime, aBeginningCount);
      },
      onFailure : function expireStartCountFailure(aError) {
        log("expireStartCountFailure");
      }
    });
  },

  shutdown: function shutdown() { dbClose(true); }
};

// Prevent add-ons from redefining this API
Object.freeze(FormHistory);
