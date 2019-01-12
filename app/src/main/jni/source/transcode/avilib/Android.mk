LOCAL_PATH :=$(call my-dir)

#转码 avilib

#源文件
MY_AVILIB_SRC_FILES := avilib.c platform_posix.c

#包含导出路径
MY_AVILIB_C_INCLUDES := $(LOCAL_PATH)

#avilib静态
include $(CLEAR_VARS)

#模块名称
LOCAL_MODULE := avilib_static

#源文件
LOCAL_SRC_FILES := $(MY_AVILIB_SRC_FILES)

#包含导出路径
LOCAL_EXPORT_C_INCLUDES := $(MY_AVILIB_C_INCLUDES)

#构建静态库
include $(BUILD_STATIC_LIBRARY)

#avilib共享
include $(CLEAR_VARS)

#模块名称
LOCAL_MODULE := avilib_shared

#源文件
LOCAL_SRC_FILES := $(MY_AVILIB_SRC_FILES)

#包含导出路径
LOCAL_EXPORT_C_INCLUDES := $(MY_AVILIB_C_INCLUDES)

#构建共享库
include $(BUILD_SHARED_LIBRARY)