LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := game-gl
LOCAL_SRC_FILES := game-gl.c
LOCAL_LDLIBS := -lGLESv2
include $(BUILD_SHARED_LIBRARY)
