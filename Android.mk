LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := dobby
LOCAL_SRC_FILES := libraries/$(TARGET_ARCH_ABI)/libdobby.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := GlossHook
LOCAL_SRC_FILES := libraries/$(TARGET_ARCH_ABI)/libGlossHook.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := patcher
LOCAL_WHOLE_STATIC_LIBRARIES := dobby GlossHook
LOCAL_SRC_FILES := src/main.cpp

LOCAL_CPP_FEATURES += exceptions
LOCAL_CFLAGS := -O2 -w -s -Wno-error=format-security -fvisibility=hidden -fpermissive -fexceptions
LOCAL_CPPFLAGS := -O2 -w -s -Wno-error=format-security -fvisibility=hidden -Werror -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fpermissive -Wall -fexceptions  
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all,-llog
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_LDLIBS := -llog -landroid -lm

include $(BUILD_SHARED_LIBRARY)
