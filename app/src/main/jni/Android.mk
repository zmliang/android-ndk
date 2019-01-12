LOCAL_PATH :=$(call my-dir)
include $(CLEAR_VARS)

LOCAL_LDLIBS += -llog \
    -ljnigraphics



LOCAL_MODULE :=AVIPlayer
LOCAL_SRC_FILES :=\
    Common.cpp \
    test_zml_com_myndk_AbstractPlayerActivity.cpp \
    test_zml_com_myndk_BitmapPlayerActivity.cpp

LOCAL_STATIC_LIBRARIES += avilib_static

include $(BUILD_SHARED_LIBRARY)


$(call import-add-path, D:\my\androidStudioProjects\myNDK\app\src\main\jni)\

#$(call import-add-path, D:\my\androidStudioProjects\myNDK\app\src\main\jni\source\transcode\avilib)\

$(call import-module,source/transcode/avilib)