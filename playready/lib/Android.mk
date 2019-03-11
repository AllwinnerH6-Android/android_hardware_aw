LOCAL_PATH:= $(call my-dir)

#####################################################################
# libplayreadydrmplugin.so
####################################################################
include $(CLEAR_VARS)

LOCAL_MODULE := libplayreadydrmplugin

ifeq ($(BOARD_PLAYREADY_USE_SECUREOS), 1)
LOCAL_SRC_FILES := \
    secure/libplayreadydrmplugin.so
else
LOCAL_SRC_FILES := \
    nonsecure/libplayreadydrmplugin.so
endif
$(warning libplayreadypk=$(LOCAL_SRC_FILES))
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_TAGS := optional
LOCAL_MULTILIB := 32
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_RELATIVE_PATH := mediadrm
include $(BUILD_PREBUILT)

#####################################################################
# libplayreadypk.so
#####################################################################
include $(CLEAR_VARS)
LOCAL_MODULE := libplayreadypk
ifeq ($(BOARD_PLAYREADY_USE_SECUREOS), 1)
LOCAL_SRC_FILES := \
    secure/libplayreadypk.so
else
LOCAL_SRC_FILES := \
    nonsecure/libplayreadypk.so
endif
$(warning libplayreadypk=$(LOCAL_SRC_FILES))
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_TAGS := optional
LOCAL_MULTILIB := 32
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)
