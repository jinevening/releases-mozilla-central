/* WARNING - This file is autogenerated by mobile/android/base/jni-generator.py. Do not edit manually! */
#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_nativeInit_t)(JNIEnv *, jclass);
static Java_org_mozilla_gecko_GeckoAppShell_nativeInit_t f_Java_org_mozilla_gecko_GeckoAppShell_nativeInit;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_nativeInit(JNIEnv * arg0, jclass arg1) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_nativeInit) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_nativeInit(arg0, arg1);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_nativeInit", &f_Java_org_mozilla_gecko_GeckoAppShell_nativeInit);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_setLayerClient_t)(JNIEnv *, jclass, jobject);
static Java_org_mozilla_gecko_GeckoAppShell_setLayerClient_t f_Java_org_mozilla_gecko_GeckoAppShell_setLayerClient;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_setLayerClient(JNIEnv * arg0, jclass arg1, jobject arg2) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_setLayerClient) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_setLayerClient(arg0, arg1, arg2);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_setLayerClient", &f_Java_org_mozilla_gecko_GeckoAppShell_setLayerClient);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_onResume_t)(JNIEnv *, jclass);
static Java_org_mozilla_gecko_GeckoAppShell_onResume_t f_Java_org_mozilla_gecko_GeckoAppShell_onResume;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_onResume(JNIEnv * arg0, jclass arg1) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_onResume) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_onResume(arg0, arg1);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_onResume", &f_Java_org_mozilla_gecko_GeckoAppShell_onResume);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_onLowMemory_t)(JNIEnv *, jclass);
static Java_org_mozilla_gecko_GeckoAppShell_onLowMemory_t f_Java_org_mozilla_gecko_GeckoAppShell_onLowMemory;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_onLowMemory(JNIEnv * arg0, jclass arg1) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_onLowMemory) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_onLowMemory(arg0, arg1);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_onLowMemory", &f_Java_org_mozilla_gecko_GeckoAppShell_onLowMemory);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_callObserver_t)(JNIEnv *, jclass, jstring, jstring, jstring);
static Java_org_mozilla_gecko_GeckoAppShell_callObserver_t f_Java_org_mozilla_gecko_GeckoAppShell_callObserver;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_callObserver(JNIEnv * arg0, jclass arg1, jstring arg2, jstring arg3, jstring arg4) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_callObserver) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_callObserver(arg0, arg1, arg2, arg3, arg4);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_callObserver", &f_Java_org_mozilla_gecko_GeckoAppShell_callObserver);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_removeObserver_t)(JNIEnv *, jclass, jstring);
static Java_org_mozilla_gecko_GeckoAppShell_removeObserver_t f_Java_org_mozilla_gecko_GeckoAppShell_removeObserver;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_removeObserver(JNIEnv * arg0, jclass arg1, jstring arg2) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_removeObserver) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_removeObserver(arg0, arg1, arg2);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_removeObserver", &f_Java_org_mozilla_gecko_GeckoAppShell_removeObserver);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_onChangeNetworkLinkStatus_t)(JNIEnv *, jclass, jstring);
static Java_org_mozilla_gecko_GeckoAppShell_onChangeNetworkLinkStatus_t f_Java_org_mozilla_gecko_GeckoAppShell_onChangeNetworkLinkStatus;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_onChangeNetworkLinkStatus(JNIEnv * arg0, jclass arg1, jstring arg2) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_onChangeNetworkLinkStatus) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_onChangeNetworkLinkStatus(arg0, arg1, arg2);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_onChangeNetworkLinkStatus", &f_Java_org_mozilla_gecko_GeckoAppShell_onChangeNetworkLinkStatus);
#endif

#ifdef JNI_STUBS

typedef jobject (*Java_org_mozilla_gecko_GeckoAppShell_getNextMessageFromQueue_t)(JNIEnv *, jclass, jobject);
static Java_org_mozilla_gecko_GeckoAppShell_getNextMessageFromQueue_t f_Java_org_mozilla_gecko_GeckoAppShell_getNextMessageFromQueue;
extern "C" NS_EXPORT jobject JNICALL
Java_org_mozilla_gecko_GeckoAppShell_getNextMessageFromQueue(JNIEnv * arg0, jclass arg1, jobject arg2) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_getNextMessageFromQueue) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return NULL;
    }
    return f_Java_org_mozilla_gecko_GeckoAppShell_getNextMessageFromQueue(arg0, arg1, arg2);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_getNextMessageFromQueue", &f_Java_org_mozilla_gecko_GeckoAppShell_getNextMessageFromQueue);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_onSurfaceTextureFrameAvailable_t)(JNIEnv *, jclass, jobject, jint);
static Java_org_mozilla_gecko_GeckoAppShell_onSurfaceTextureFrameAvailable_t f_Java_org_mozilla_gecko_GeckoAppShell_onSurfaceTextureFrameAvailable;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_onSurfaceTextureFrameAvailable(JNIEnv * arg0, jclass arg1, jobject arg2, jint arg3) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_onSurfaceTextureFrameAvailable) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_onSurfaceTextureFrameAvailable(arg0, arg1, arg2, arg3);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_onSurfaceTextureFrameAvailable", &f_Java_org_mozilla_gecko_GeckoAppShell_onSurfaceTextureFrameAvailable);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_reportJavaCrash_t)(JNIEnv *, jclass, jstring);
static Java_org_mozilla_gecko_GeckoAppShell_reportJavaCrash_t f_Java_org_mozilla_gecko_GeckoAppShell_reportJavaCrash;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_reportJavaCrash(JNIEnv * arg0, jclass arg1, jstring arg2) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_reportJavaCrash) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_reportJavaCrash(arg0, arg1, arg2);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_reportJavaCrash", &f_Java_org_mozilla_gecko_GeckoAppShell_reportJavaCrash);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_processNextNativeEvent_t)(JNIEnv *, jclass);
static Java_org_mozilla_gecko_GeckoAppShell_processNextNativeEvent_t f_Java_org_mozilla_gecko_GeckoAppShell_processNextNativeEvent;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_processNextNativeEvent(JNIEnv * arg0, jclass arg1) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_processNextNativeEvent) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_processNextNativeEvent(arg0, arg1);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_processNextNativeEvent", &f_Java_org_mozilla_gecko_GeckoAppShell_processNextNativeEvent);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifyBatteryChange_t)(JNIEnv *, jclass, jdouble, jboolean, jdouble);
static Java_org_mozilla_gecko_GeckoAppShell_notifyBatteryChange_t f_Java_org_mozilla_gecko_GeckoAppShell_notifyBatteryChange;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifyBatteryChange(JNIEnv * arg0, jclass arg1, jdouble arg2, jboolean arg3, jdouble arg4) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifyBatteryChange) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifyBatteryChange(arg0, arg1, arg2, arg3, arg4);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifyBatteryChange", &f_Java_org_mozilla_gecko_GeckoAppShell_notifyBatteryChange);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifySmsReceived_t)(JNIEnv *, jclass, jstring, jstring, jint, jlong);
static Java_org_mozilla_gecko_GeckoAppShell_notifySmsReceived_t f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsReceived;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifySmsReceived(JNIEnv * arg0, jclass arg1, jstring arg2, jstring arg3, jint arg4, jlong arg5) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsReceived) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsReceived(arg0, arg1, arg2, arg3, arg4, arg5);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifySmsReceived", &f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsReceived);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifySmsSent_t)(JNIEnv *, jclass, jint, jstring, jstring, jlong, jint);
static Java_org_mozilla_gecko_GeckoAppShell_notifySmsSent_t f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsSent;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifySmsSent(JNIEnv * arg0, jclass arg1, jint arg2, jstring arg3, jstring arg4, jlong arg5, jint arg6) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsSent) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsSent(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifySmsSent", &f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsSent);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifySmsDelivery_t)(JNIEnv *, jclass, jint, jint, jstring, jstring, jlong);
static Java_org_mozilla_gecko_GeckoAppShell_notifySmsDelivery_t f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsDelivery;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifySmsDelivery(JNIEnv * arg0, jclass arg1, jint arg2, jint arg3, jstring arg4, jstring arg5, jlong arg6) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsDelivery) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsDelivery(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifySmsDelivery", &f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsDelivery);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifySmsSendFailed_t)(JNIEnv *, jclass, jint, jint);
static Java_org_mozilla_gecko_GeckoAppShell_notifySmsSendFailed_t f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsSendFailed;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifySmsSendFailed(JNIEnv * arg0, jclass arg1, jint arg2, jint arg3) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsSendFailed) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsSendFailed(arg0, arg1, arg2, arg3);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifySmsSendFailed", &f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsSendFailed);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifyGetSms_t)(JNIEnv *, jclass, jint, jint, jstring, jstring, jstring, jlong, jint);
static Java_org_mozilla_gecko_GeckoAppShell_notifyGetSms_t f_Java_org_mozilla_gecko_GeckoAppShell_notifyGetSms;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifyGetSms(JNIEnv * arg0, jclass arg1, jint arg2, jint arg3, jstring arg4, jstring arg5, jstring arg6, jlong arg7, jint arg8) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifyGetSms) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifyGetSms(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifyGetSms", &f_Java_org_mozilla_gecko_GeckoAppShell_notifyGetSms);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifyGetSmsFailed_t)(JNIEnv *, jclass, jint, jint);
static Java_org_mozilla_gecko_GeckoAppShell_notifyGetSmsFailed_t f_Java_org_mozilla_gecko_GeckoAppShell_notifyGetSmsFailed;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifyGetSmsFailed(JNIEnv * arg0, jclass arg1, jint arg2, jint arg3) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifyGetSmsFailed) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifyGetSmsFailed(arg0, arg1, arg2, arg3);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifyGetSmsFailed", &f_Java_org_mozilla_gecko_GeckoAppShell_notifyGetSmsFailed);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleted_t)(JNIEnv *, jclass, jboolean, jint);
static Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleted_t f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleted;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleted(JNIEnv * arg0, jclass arg1, jboolean arg2, jint arg3) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleted) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleted(arg0, arg1, arg2, arg3);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleted", &f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleted);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleteFailed_t)(JNIEnv *, jclass, jint, jint);
static Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleteFailed_t f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleteFailed;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleteFailed(JNIEnv * arg0, jclass arg1, jint arg2, jint arg3) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleteFailed) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleteFailed(arg0, arg1, arg2, arg3);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleteFailed", &f_Java_org_mozilla_gecko_GeckoAppShell_notifySmsDeleteFailed);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifyNoMessageInList_t)(JNIEnv *, jclass, jint);
static Java_org_mozilla_gecko_GeckoAppShell_notifyNoMessageInList_t f_Java_org_mozilla_gecko_GeckoAppShell_notifyNoMessageInList;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifyNoMessageInList(JNIEnv * arg0, jclass arg1, jint arg2) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifyNoMessageInList) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifyNoMessageInList(arg0, arg1, arg2);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifyNoMessageInList", &f_Java_org_mozilla_gecko_GeckoAppShell_notifyNoMessageInList);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifyListCreated_t)(JNIEnv *, jclass, jint, jint, jint, jstring, jstring, jstring, jlong, jint);
static Java_org_mozilla_gecko_GeckoAppShell_notifyListCreated_t f_Java_org_mozilla_gecko_GeckoAppShell_notifyListCreated;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifyListCreated(JNIEnv * arg0, jclass arg1, jint arg2, jint arg3, jint arg4, jstring arg5, jstring arg6, jstring arg7, jlong arg8, jint arg9) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifyListCreated) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifyListCreated(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifyListCreated", &f_Java_org_mozilla_gecko_GeckoAppShell_notifyListCreated);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifyGotNextMessage_t)(JNIEnv *, jclass, jint, jint, jstring, jstring, jstring, jlong, jint);
static Java_org_mozilla_gecko_GeckoAppShell_notifyGotNextMessage_t f_Java_org_mozilla_gecko_GeckoAppShell_notifyGotNextMessage;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifyGotNextMessage(JNIEnv * arg0, jclass arg1, jint arg2, jint arg3, jstring arg4, jstring arg5, jstring arg6, jlong arg7, jint arg8) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifyGotNextMessage) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifyGotNextMessage(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifyGotNextMessage", &f_Java_org_mozilla_gecko_GeckoAppShell_notifyGotNextMessage);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifyReadingMessageListFailed_t)(JNIEnv *, jclass, jint, jint);
static Java_org_mozilla_gecko_GeckoAppShell_notifyReadingMessageListFailed_t f_Java_org_mozilla_gecko_GeckoAppShell_notifyReadingMessageListFailed;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifyReadingMessageListFailed(JNIEnv * arg0, jclass arg1, jint arg2, jint arg3) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifyReadingMessageListFailed) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifyReadingMessageListFailed(arg0, arg1, arg2, arg3);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifyReadingMessageListFailed", &f_Java_org_mozilla_gecko_GeckoAppShell_notifyReadingMessageListFailed);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_scheduleComposite_t)(JNIEnv *, jclass);
static Java_org_mozilla_gecko_GeckoAppShell_scheduleComposite_t f_Java_org_mozilla_gecko_GeckoAppShell_scheduleComposite;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_scheduleComposite(JNIEnv * arg0, jclass arg1) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_scheduleComposite) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_scheduleComposite(arg0, arg1);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_scheduleComposite", &f_Java_org_mozilla_gecko_GeckoAppShell_scheduleComposite);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_schedulePauseComposition_t)(JNIEnv *, jclass);
static Java_org_mozilla_gecko_GeckoAppShell_schedulePauseComposition_t f_Java_org_mozilla_gecko_GeckoAppShell_schedulePauseComposition;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_schedulePauseComposition(JNIEnv * arg0, jclass arg1) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_schedulePauseComposition) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_schedulePauseComposition(arg0, arg1);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_schedulePauseComposition", &f_Java_org_mozilla_gecko_GeckoAppShell_schedulePauseComposition);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_scheduleResumeComposition_t)(JNIEnv *, jclass, jint, jint);
static Java_org_mozilla_gecko_GeckoAppShell_scheduleResumeComposition_t f_Java_org_mozilla_gecko_GeckoAppShell_scheduleResumeComposition;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_scheduleResumeComposition(JNIEnv * arg0, jclass arg1, jint arg2, jint arg3) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_scheduleResumeComposition) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_scheduleResumeComposition(arg0, arg1, arg2, arg3);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_scheduleResumeComposition", &f_Java_org_mozilla_gecko_GeckoAppShell_scheduleResumeComposition);
#endif

#ifdef JNI_STUBS

typedef jfloat (*Java_org_mozilla_gecko_GeckoAppShell_computeRenderIntegrity_t)(JNIEnv *, jclass);
static Java_org_mozilla_gecko_GeckoAppShell_computeRenderIntegrity_t f_Java_org_mozilla_gecko_GeckoAppShell_computeRenderIntegrity;
extern "C" NS_EXPORT jfloat JNICALL
Java_org_mozilla_gecko_GeckoAppShell_computeRenderIntegrity(JNIEnv * arg0, jclass arg1) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_computeRenderIntegrity) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return 0;
    }
    return f_Java_org_mozilla_gecko_GeckoAppShell_computeRenderIntegrity(arg0, arg1);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_computeRenderIntegrity", &f_Java_org_mozilla_gecko_GeckoAppShell_computeRenderIntegrity);
#endif

#ifdef JNI_STUBS

typedef jobject (*Java_org_mozilla_gecko_GeckoAppShell_getSurfaceBits_t)(JNIEnv *, jclass, jobject);
static Java_org_mozilla_gecko_GeckoAppShell_getSurfaceBits_t f_Java_org_mozilla_gecko_GeckoAppShell_getSurfaceBits;
extern "C" NS_EXPORT jobject JNICALL
Java_org_mozilla_gecko_GeckoAppShell_getSurfaceBits(JNIEnv * arg0, jclass arg1, jobject arg2) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_getSurfaceBits) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return NULL;
    }
    return f_Java_org_mozilla_gecko_GeckoAppShell_getSurfaceBits(arg0, arg1, arg2);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_getSurfaceBits", &f_Java_org_mozilla_gecko_GeckoAppShell_getSurfaceBits);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_onFullScreenPluginHidden_t)(JNIEnv *, jclass, jobject);
static Java_org_mozilla_gecko_GeckoAppShell_onFullScreenPluginHidden_t f_Java_org_mozilla_gecko_GeckoAppShell_onFullScreenPluginHidden;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_onFullScreenPluginHidden(JNIEnv * arg0, jclass arg1, jobject arg2) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_onFullScreenPluginHidden) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_onFullScreenPluginHidden(arg0, arg1, arg2);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_onFullScreenPluginHidden", &f_Java_org_mozilla_gecko_GeckoAppShell_onFullScreenPluginHidden);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifyGeckoOfEvent_t)(JNIEnv *, jclass, jobject);
static Java_org_mozilla_gecko_GeckoAppShell_notifyGeckoOfEvent_t f_Java_org_mozilla_gecko_GeckoAppShell_notifyGeckoOfEvent;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifyGeckoOfEvent(JNIEnv * arg0, jclass arg1, jobject arg2) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifyGeckoOfEvent) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifyGeckoOfEvent(arg0, arg1, arg2);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifyGeckoOfEvent", &f_Java_org_mozilla_gecko_GeckoAppShell_notifyGeckoOfEvent);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_cameraCallbackBridge_t)(JNIEnv *, jclass, jbyteArray);
static Java_org_mozilla_gecko_GeckoAppShell_cameraCallbackBridge_t f_Java_org_mozilla_gecko_GeckoAppShell_cameraCallbackBridge;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_cameraCallbackBridge(JNIEnv * arg0, jclass arg1, jbyteArray arg2) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_cameraCallbackBridge) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_cameraCallbackBridge(arg0, arg1, arg2);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_cameraCallbackBridge", &f_Java_org_mozilla_gecko_GeckoAppShell_cameraCallbackBridge);
#endif

#ifdef JNI_STUBS

typedef void (*Java_org_mozilla_gecko_GeckoAppShell_notifyFilePickerResult_t)(JNIEnv *, jclass, jstring, jlong);
static Java_org_mozilla_gecko_GeckoAppShell_notifyFilePickerResult_t f_Java_org_mozilla_gecko_GeckoAppShell_notifyFilePickerResult;
extern "C" NS_EXPORT void JNICALL
Java_org_mozilla_gecko_GeckoAppShell_notifyFilePickerResult(JNIEnv * arg0, jclass arg1, jstring arg2, jlong arg3) {
    if (!f_Java_org_mozilla_gecko_GeckoAppShell_notifyFilePickerResult) {
        arg0->ThrowNew(arg0->FindClass("java/lang/UnsupportedOperationException"),
                       "JNI Function called before it was loaded");
        return ;
    }
     f_Java_org_mozilla_gecko_GeckoAppShell_notifyFilePickerResult(arg0, arg1, arg2, arg3);
}
#endif

#ifdef JNI_BINDINGS
  xul_dlsym("Java_org_mozilla_gecko_GeckoAppShell_notifyFilePickerResult", &f_Java_org_mozilla_gecko_GeckoAppShell_notifyFilePickerResult);
#endif
