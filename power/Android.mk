# Copyright (C) 2011 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := power.$(TARGET_BOARD_PLATFORM)
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_PROPRIETARY_MODULE := true
LOCAL_SRC_FILES := power.c
LOCAL_C_INCLUDES += \
        system/core/libutils/include \
        hardware/libhardware/include \
        system/core/libsystem/include

LOCAL_CFLAGS += -Wno-unused-parameter

ifeq ($(TARGET_BOARD_PLATFORM), astar)
LOCAL_CFLAGS   += -DA33
LOCAL_SRC_FILES += platform/SUN8IW5P1_A33.c

endif

ifeq ($(TARGET_BOARD_PLATFORM), tulip)
LOCAL_CFLAGS   += -DA64
LOCAL_SRC_FILES += platform/SUN50IW1P1_A64.c

endif

ifeq ($(TARGET_BOARD_PLATFORM), kylin)
LOCAL_CFLAGS   += -DA80
LOCAL_SRC_FILES += platform/SUN9IW1P1_A80.c
endif

ifeq ($(TARGET_BOARD_PLATFORM), octopus)
LOCAL_CFLAGS   += -DA83T
LOCAL_SRC_FILES += platform/SUN8IW6P1_A83T.c
endif

ifeq ($(TARGET_BOARD_PLATFORM), eagle)
LOCAL_CFLAGS   += -DA83T
LOCAL_SRC_FILES += platform/SUN8IW6P1_A83T.c
endif

ifeq ($(TARGET_BOARD_PLATFORM), neptune)
LOCAL_CFLAGS   += -DVR9
LOCAL_SRC_FILES += platform/SUN50IW3P1_VR9.c
endif

ifeq ($(TARGET_BOARD_PLATFORM), uranus)
LOCAL_CFLAGS   += -DA63
LOCAL_SRC_FILES += platform/SUN50IW3P1_A63.c
endif

ifeq ($(TARGET_BOARD_PLATFORM), venus)
LOCAL_CFLAGS   += -DA50
LOCAL_SRC_FILES += platform/SUN8IW15P1_A50.c
endif

ifeq ($(TARGET_BOARD_PLATFORM), petrel)
LOCAL_CFLAGS   += -DH6
LOCAL_SRC_FILES += platform/SUN50IW6P1_H6.c
endif


LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)



include $(CLEAR_VARS)

LOCAL_SRC_FILES:= powertest.c

LOCAL_MODULE:= powertest

LOCAL_C_INCLUDES :=

LOCAL_CFLAGS += -Wno-unused-parameter


LOCAL_SHARED_LIBRARIES := libcutils liblog

ifeq ($(TARGET_BOARD_PLATFORM), astar)
LOCAL_CFLAGS   += -DA33
LOCAL_SRC_FILES += platform/SUN8IW5P1_A33.c

endif

ifeq ($(TARGET_BOARD_PLATFORM), tulip)
LOCAL_CFLAGS   += -DA64
LOCAL_SRC_FILES += platform/SUN50IW1P1_A64.c
endif

ifeq ($(TARGET_BOARD_PLATFORM), kylin)
LOCAL_CFLAGS   += -DA80
LOCAL_SRC_FILES += platform/SUN9IW1P1_A80.c
endif

ifeq ($(TARGET_BOARD_PLATFORM), octopus)
LOCAL_CFLAGS   += -DA83T
LOCAL_SRC_FILES += platform/SUN8IW6P1_A83T.c
endif

ifeq ($(TARGET_BOARD_PLATFORM), eagle)
LOCAL_CFLAGS   += -DA83T
LOCAL_SRC_FILES += platform/SUN8IW6P1_A83T.c
endif

ifeq ($(TARGET_BOARD_PLATFORM), neptune)
LOCAL_CFLAGS   += -DVR9
LOCAL_SRC_FILES += platform/SUN50IW3P1_VR9.c
endif

ifeq ($(TARGET_BOARD_PLATFORM), uranus)
LOCAL_CFLAGS   += -DA63
LOCAL_SRC_FILES += platform/SUN50IW3P1_A63.c
endif

ifeq ($(TARGET_BOARD_PLATFORM), venus)
LOCAL_CFLAGS   += -DA50
LOCAL_SRC_FILES += platform/SUN8IW15P1_A50.c
endif

ifeq ($(TARGET_BOARD_PLATFORM), petrel)
LOCAL_CFLAGS   += -DH6
LOCAL_SRC_FILES += platform/SUN50IW6P1_H6.c
endif


include $(BUILD_EXECUTABLE)

