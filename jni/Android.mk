LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := fmod
LOCAL_SRC_FILES := libfmod.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := fmodL
LOCAL_SRC_FILES := libfmodL.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_MODULE    := qq_voice
LOCAL_SRC_FILES := effect_fix.cpp
LOCAL_SHARED_LIBRARIES := fmod fmodL
#添加log支持
LOCAL_LDLIBS := -llog
#添加c++异常类支持
LOCAL_CPP_FEATURES := exceptions
include $(BUILD_SHARED_LIBRARY)
