CAMERA_HAL_LOCAL_PATH := $(call my-dir)

# Prevent the HAL from building on devices not specifically
# requesting to use it.
ifeq ($(USE_CAMERA_HAL_1_0), true)
#ifeq (true, true)

ifneq ($(filter venus%,$(TARGET_BOARD_PLATFORM)),)
include $(call all-subdir-makefiles)
endif
LOCAL_PATH := $(CAMERA_HAL_LOCAL_PATH)

########## configure CONF_ANDROID_VERSION ##########
android_version = $(shell echo $(PLATFORM_VERSION) | cut -c 1)

ifeq ($(android_version), 7)
    LOCAL_CFLAGS += -DUSE_SHARE_BUFFER
    #$(warning "android_version 7 : $(PLATFORM_VERSION)")
else ifeq ($(android_version), 8)
    LOCAL_CFLAGS += -DUSE_SHARE_BUFFER
    #$(warning "android_version 8 : $(PLATFORM_VERSION)")
else ifeq ($(android_version), 9)
    LOCAL_CFLAGS += -DUSE_SHARE_BUFFER
    #$(warning "android_version 9 : $(PLATFORM_VERSION)")
endif
####################################################


#$(warning $(TARGET_BOARD_PLATFORM))
############################################################################
#####---A64---
ifneq ($(filter tulip%,$(TARGET_BOARD_PLATFORM)),)
include $(CLEAR_VARS)
LOCAL_MODULE := libfacedetection
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libfacedetection.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libfacedetection.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libSmileEyeBlink
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libSmileEyeBlink.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libSmileEyeBlink.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libapperceivepeople
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libapperceivepeople.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libapperceivepeople.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
endif
############################################################################


############################################################################
#####---H6---
ifneq ($(filter petrel%,$(TARGET_BOARD_PLATFORM)),)
include $(CLEAR_VARS)
LOCAL_MODULE := libfacedetection
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libfacedetection.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libfacedetection.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libSmileEyeBlink
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libSmileEyeBlink.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libSmileEyeBlink.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libapperceivepeople
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libapperceivepeople.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libapperceivepeople.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS += -DUSE_IOMMU_DRIVER
include $(BUILD_PREBUILT)
endif
############################################################################

############################################################################
#####---A50---
ifneq ($(filter venus%,$(TARGET_BOARD_PLATFORM)),)
include $(CLEAR_VARS)
LOCAL_MODULE := libfacedetection
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libfacedetection.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libfacedetection.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
#include $(CLEAR_VARS)
#LOCAL_MODULE := libSmileEyeBlink
#LOCAL_MODULE_SUFFIX := .so
#LOCAL_MODULE_CLASS := SHARED_LIBRARIES
#LOCAL_SRC_FILES_32 := lib32/facedetection/libSmileEyeBlink.so
#LOCAL_SRC_FILES_64 := lib64/facedetection/libSmileEyeBlink.so
#LOCAL_MULTILIB:= both
#LOCAL_MODULE_TAGS := optional
#include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libapperceivepeople
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libapperceivepeople.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libapperceivepeople.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
endif
############################################################################

############################################################################
#####---A83---
ifneq ($(filter octopus%,$(TARGET_BOARD_PLATFORM)),)
include $(CLEAR_VARS)
LOCAL_MODULE := libfacedetection
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libfacedetection.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libfacedetection.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libSmileEyeBlink
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libSmileEyeBlink.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libSmileEyeBlink.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libapperceivepeople
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libapperceivepeople.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libapperceivepeople.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
endif
############################################################################

############################################################################
#####---A33---
ifneq ($(filter astar%,$(TARGET_BOARD_PLATFORM)),)
include $(CLEAR_VARS)
LOCAL_MODULE := libfacedetection
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libfacedetection.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libfacedetection.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libSmileEyeBlink
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libSmileEyeBlink.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libSmileEyeBlink.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libapperceivepeople
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libapperceivepeople.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libapperceivepeople.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
endif
############################################################################

############################################################################
#####---A80---
ifneq ($(filter kylin%,$(TARGET_BOARD_PLATFORM)),)
include $(CLEAR_VARS)
LOCAL_MODULE := libfacedetection
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libfacedetection.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libfacedetection.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libSmileEyeBlink
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libSmileEyeBlink.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libSmileEyeBlink.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libapperceivepeople
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libapperceivepeople.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libapperceivepeople.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
endif
############################################################################

############################################################################
#####---A63---
ifneq ($(filter uranus%,$(TARGET_BOARD_PLATFORM)),)
include $(CLEAR_VARS)
LOCAL_MODULE := libfacedetection
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libfacedetection.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libfacedetection.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libSmileEyeBlink
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libSmileEyeBlink.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libSmileEyeBlink.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libapperceivepeople
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libapperceivepeople.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libapperceivepeople.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
endif
############################################################################

############################################################################
#####---VR9---
ifneq ($(filter neptune%,$(TARGET_BOARD_PLATFORM)),)
include $(CLEAR_VARS)
LOCAL_MODULE := libfacedetection
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libfacedetection.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libfacedetection.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libSmileEyeBlink
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libSmileEyeBlink.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libSmileEyeBlink.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libapperceivepeople
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/facedetection/libapperceivepeople.so
LOCAL_SRC_FILES_64 := lib64/facedetection/libapperceivepeople.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
endif
############################################################################

include $(CLEAR_VARS)
LOCAL_MODULE := libproc
LOCAL_MODULE_SUFFIX := .so
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/proc/libproc.so
LOCAL_SRC_FILES_64 := lib64/proc/libproc.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := libhdr
LOCAL_MODULE_SUFFIX := .so
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_32 := lib32/hdr/libhdr.so
LOCAL_SRC_FILES_64 := lib64/hdr/libhdr.so
LOCAL_MULTILIB:= both
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
# LOCAL_MODULE_RELATIVE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_PROPRIETARY_MODULE := true

LOCAL_CFLAGS += -Wall  -Wno-unused-parameter -Wno-macro-redefined -Wno-unused-parameter -Wno-extra-tokens -Wno-null-arithmetic -Wno-format -Wno-reorder -Wno-unused-variable -Wno-writable-strings -Wno-logical-op-parentheses -Wno-sign-compare \
				-Wno-unused-parameter -Wno-unused-value -Wno-unused-function -Wno-parentheses -Wno-extern-c-compat -Wno-null-conversion -Wno-sometimes-uninitialized -Wno-gnu-designator
	
LOCAL_SHARED_LIBRARIES:= \
    libbinder \
    libutils \
    libcutils \
    libui \
    liblog \
    libexpat

LOCAL_SHARED_LIBRARIES += \
    libhdr \
    libvdecoder.vendor \
	libvencoder.vendor \
    libproc

LOCAL_C_INCLUDES +=                                 \
    frameworks/base/core/jni/android/graphics         \
    frameworks/native/include/media/openmax            \
    hardware/libhardware/include/hardware            \
    frameworks/native/include                        \
    frameworks/native/libs/nativewindow/include		\
    frameworks/native/include/media/hardware         \
    system/media/camera/include/                \
    hardware/aw/camera/1_0/include        \
    hardware/aw/camera        \
    system/core/libion/include \
    system/core/include \
    system/core/include/utils \
    system/core/liblog/include \
    $(TARGET_HARDWARE_INCLUDE)

LOCAL_SRC_FILES := \
    memory/memoryAdapter.c \
    memory/ionMemory/ionAlloc.c \
    HALCameraFactory.cpp \
    PreviewWindow.cpp \
	CameraParameters.cpp \
	CallbackNotifier.cpp \
    CCameraConfig.cpp \
    BufferListManager.cpp \
    OSAL_Mutex.c \
    OSAL_Queue.c \
    scaler.c \
    Libve_Decoder2.c \
    CameraDebug.cpp \
    SceneFactory/HDRSceneMode.cpp \
    SceneFactory/NightSceneMode.cpp \
    SceneFactory/SceneModeFactory.cpp

ifeq ($(USE_IOMMU),true)
    LOCAL_CFLAGS += -DUSE_IOMMU
endif

# choose hal for new driver or old
SUPPORT_NEW_DRIVER := Y

ifeq ($(SUPPORT_NEW_DRIVER),Y)
LOCAL_CFLAGS += -DSUPPORT_NEW_DRIVER -DTARGET_BOARD_PLATFORM=$(TARGET_BOARD_PLATFORM) -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)
LOCAL_SRC_FILES += \
    CameraHardware2.cpp \
    V4L2CameraDevice2.cpp
else
LOCAL_SRC_FILES += \
    CameraHardware.cpp \
    V4L2CameraDevice.cpp
endif


########## configure CONF_ANDROID_VERSION ##########
android_version = $(shell echo $(PLATFORM_VERSION) | cut -c 1)

ifeq ($(android_version), 7)
    LOCAL_CFLAGS += -DUSE_SHARE_BUFFER
    #$(warning "android_version 7 : $(PLATFORM_VERSION)")
else ifeq ($(android_version), 8)
    LOCAL_CFLAGS += -DUSE_SHARE_BUFFER
    #$(warning "android_version 8 : $(PLATFORM_VERSION)")
else ifeq ($(android_version), 9)
    LOCAL_CFLAGS += -DUSE_SHARE_BUFFER
    #$(warning "android_version 9 : $(PLATFORM_VERSION)")
endif
####################################################

############################################################################
#####---A64---
ifneq ($(filter tulip%,$(TARGET_BOARD_PLATFORM)),)
LOCAL_CFLAGS += -D__A64__
LOCAL_C_INCLUDES += \
    frameworks/av/media/libcedarc/include \
    hardware/aw/camera/libfacedetection \
    hardware/aw/camera/SceneFactory

LOCAL_SHARED_LIBRARIES += \
    libvencoder \
    libfacedetection \
    libSmileEyeBlink \
    libapperceivepeople
endif

############################################################################

############################################################################
#####---H6---
ifneq ($(filter petrel%,$(TARGET_BOARD_PLATFORM)),)
LOCAL_CFLAGS += -D__H6__
LOCAL_CFLAGS += -DUSE_IOMMU_DRIVER
LOCAL_C_INCLUDES += \
    frameworks/av/media/libcedarc/include \
    hardware/aw/camera/libfacedetection \
    hardware/aw/camera/SceneFactory \
    system/media/camera/include/system \

#LOCAL_SHARED_LIBRARIES += \
    #libvencoder \
    #libfacedetection \
    #libSmileEyeBlink \
    #libapperceivepeople
endif

############################################################################

############################################################################
#####---A50---
ifneq ($(filter venus%,$(TARGET_BOARD_PLATFORM)),)
LOCAL_CFLAGS += -D__A50__
LOCAL_CFLAGS += -DUSE_IOMMU_DRIVER
LOCAL_C_INCLUDES += \
    frameworks/av/media/libcedarc/include \
    hardware/aw/camera/1_0/libfacedetection \
    hardware/aw/camera/1_0/SceneFactory \
    hardware/aw/camera/1_0/allwinnertech/libAWIspApi

LOCAL_SHARED_LIBRARIES += libAWIspApi  

endif

############################################################################

############################################################################
#####---A33---
ifneq ($(filter astar%,$(TARGET_BOARD_PLATFORM)),)
LOCAL_CFLAGS += -D__A33__
LOCAL_C_INCLUDES += \
    frameworks/av/media/libcedarc/include \
    hardware/aw/camera/libfacedetection \
    hardware/aw/camera/SceneFactory

LOCAL_SHARED_LIBRARIES += \
    libvencoder \
    libfacedetection \
    libSmileEyeBlink \
    libapperceivepeople
endif

############################################################################
#####---A83---
ifneq ($(filter octopus%,$(TARGET_BOARD_PLATFORM)),)
LOCAL_CFLAGS += -D__A83__
LOCAL_C_INCLUDES += \
    frameworks/av/media/libcedarc/include \
    hardware/aw/camera/libfacedetection \
    hardware/aw/camera/SceneFactory

LOCAL_SHARED_LIBRARIES += \
    libvencoder \
    libfacedetection \
    libSmileEyeBlink \
    libapperceivepeople
endif

############################################################################
#####---A80---
ifneq ($(filter kylin%,$(TARGET_BOARD_PLATFORM)),)
LOCAL_CFLAGS += -D__A80__
LOCAL_C_INCLUDES += \
    frameworks/av/media/libcedarc/include \
    hardware/aw/camera/libfacedetection \
    hardware/aw/camera/SceneFactory

LOCAL_SHARED_LIBRARIES += \
    libvencoder \
    libfacedetection \
    libSmileEyeBlink \
    libapperceivepeople
endif

###########################################################################
#####---A63---
ifneq ($(filter uranus%,$(TARGET_BOARD_PLATFORM)),)
LOCAL_CFLAGS += -D__A63__
LOCAL_C_INCLUDES += \
    frameworks/av/media/libcedarc/include \
    hardware/aw/camera/libfacedetection \
    hardware/aw/camera/SceneFactory

LOCAL_SHARED_LIBRARIES += \
    libvencoder \
    libfacedetection \
    libSmileEyeBlink \
    libapperceivepeople
endif

###########################################################################
#####---VR9---
ifneq ($(filter neptune%,$(TARGET_BOARD_PLATFORM)),)
LOCAL_CFLAGS += -D__A63__
LOCAL_C_INCLUDES += \
    frameworks/av/media/libcedarc/include \
    hardware/aw/camera/libfacedetection \
    hardware/aw/camera/SceneFactory

LOCAL_SHARED_LIBRARIES += \
    libvencoder \
    libfacedetection \
    libSmileEyeBlink \
    libapperceivepeople
endif

############################################################################

LOCAL_CFLAGS += -Wno-error=format-security
LOCAL_MODULE := camera.$(TARGET_BOARD_PLATFORM)
#$(warning $(LOCAL_MODULE))

LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

endif # USE_CAMERA_HAL_1_0
