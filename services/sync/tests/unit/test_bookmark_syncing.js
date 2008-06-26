Cu.import("resource://weave/engines/bookmarks.js");
Cu.import("resource://weave/util.js");
Cu.import("resource://weave/async.js");

Function.prototype.async = Async.sugar;

load("bookmark_setup.js");

// ----------------------------------------
// Test Logic
// ----------------------------------------

function FakeMicrosummaryService() {
  return {hasMicrosummary: function() { return false; }};
}

function makeBookmarksEngine() {
  let engine = new BookmarksEngine();
  engine._store.__ms = new FakeMicrosummaryService();
  return engine;
}

function run_test() {
  // -----
  // Setup
  // -----

  var syncTesting = new SyncTestingInfrastructure(makeBookmarksEngine);

  let bms = Cc["@mozilla.org/browser/nav-bookmarks-service;1"].
    getService(Ci.nsINavBookmarksService);

  cleanUp();

  // -----------
  // Test Proper
  // -----------

  let boogleBm = bms.insertBookmark(bms.bookmarksMenuFolder,
                                    uri("http://www.boogle.com"),
                                    -1,
                                    "Boogle");
  bms.setItemGUID(boogleBm, "boogle-bookmark-guid");

  syncTesting.doSync("initial sync w/ one bookmark");

  syncTesting.doSync("trivial re-sync");

  let yoogleBm = bms.insertBookmark(bms.bookmarksMenuFolder,
                                    uri("http://www.yoogle.com"),
                                    -1,
                                    "Yoogle");
  bms.setItemGUID(yoogleBm, "yoogle-bookmark-guid");

  syncTesting.doSync("add bookmark and re-sync");

  bms.moveItem(yoogleBm,
               bms.bookmarksMenuFolder,
               0);

  syncTesting.doSync("swap bookmark order and re-sync");

  syncTesting.saveClientState("first computer");

  syncTesting.resetClientState();

  syncTesting.doSync("re-sync on second computer");

  let zoogleBm = bms.insertBookmark(bms.bookmarksMenuFolder,
                                    uri("http://www.zoogle.com"),
                                    -1,
                                    "Zoogle");
  bms.setItemGUID(zoogleBm, "zoogle-bookmark-guid");

  syncTesting.doSync("add bookmark on second computer and resync");

  syncTesting.saveClientState("second computer");

  syncTesting.restoreClientState("first computer");
  syncTesting.doSync("re-sync on first computer");

  let binkBm1 = bms.insertBookmark(bms.bookmarksMenuFolder,
                                   uri("http://www.bink.com"),
                                   -1,
                                   "Bink");
  bms.setItemGUID(binkBm1, "bink-bookmark-guid-1");

  syncTesting.doSync("add bookmark 'bink' on first computer and resync");
  syncTesting.restoreClientState("second computer");

  let binkBm2 = bms.insertBookmark(bms.bookmarksMenuFolder,
                                   uri("http://www.bink.com"),
                                   -1,
                                   "Bink");

  bms.setItemGUID(binkBm2, "bink-bookmark-guid-2");

  syncTesting.doSync("Manually add same bookmark 'bink', but with " +
                     + "different GUID, to second computer and resync");

  // --------
  // Teardown
  // --------

  cleanUp();
}
