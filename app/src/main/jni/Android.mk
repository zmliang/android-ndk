LOCAL_PATH :=$(call my-dir)
include $(CLEAR_VARS)

LOCAL_LDLIBS += -llog \
    -ljnigraphics \
    -landroid



LOCAL_MODULE :=AVIPlayer
LOCAL_SRC_FILES :=\
    Common.cpp \
    test_zml_com_myndk_AbstractPlayerActivity.cpp \
    test_zml_com_myndk_BitmapPlayerActivity.cpp \
    test_zml_com_myndk_OpenGLPlayerActivity.cpp

LOCAL_STATIC_LIBRARIES += avilib_static

#启用GL ext原库
LOCAL_CFLAGS += -DGL_GLEXT_PROTOTYPES

#链接OpenGL ES
LOCAL_LDLIBS += -lGLESv1_CM

include $(BUILD_SHARED_LIBRARY)


$(call import-add-path, D:\my\androidStudioProjects\myNDK\app\src\main\jni)\

#$(call import-add-path, D:\my\androidStudioProjects\myNDK\app\src\main\jni\source\transcode\avilib)\

$(call import-module,source/transcode/avilib)