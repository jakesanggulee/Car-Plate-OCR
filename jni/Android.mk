LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := img
LOCAL_SRC_FILES := img.c primitive.c bitmap.c match.c fastmatch.c

include $(BUILD_SHARED_LIBRARY)
