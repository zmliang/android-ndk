//
// Created by zzz on 2019/1/11.
//
extern "C"{
#include <avilib.h>
}

#include <android/bitmap.h>


#include "Common.h"
#include "test_zml_com_myndk_BitmapPlayerActivity.h"

#define TAG "zmliang"

JNIEXPORT jlong JNICALL Java_test_zml_com_myndk_BitmapPlayerActivity_render
        (JNIEnv *env,jclass clazz,jlong avi,jobject bitmap)
{
    jboolean isFrameRead = JNI_FALSE;
    char* frameBuffer = 0;
    long frameSize = 0;
    int keyFrame = 0;
    int result;

    result =AndroidBitmap_lockPixels(env,bitmap, reinterpret_cast<void **>(&frameBuffer));

    if (ANDROID_BITMAP_RESULT_SUCCESS !=result)
    {
        ThrowException(env,"java/io/IOException","Unable to lock pixels");
        goto exit;
    }
    frameSize = AVI_read_frame((avi_t*)avi,frameBuffer,&keyFrame);
    result =AndroidBitmap_unlockPixels(env,bitmap);
    if (ANDROID_BITMAP_RESULT_SUCCESS !=result)
    {
        ThrowException(env,"java/io/IOException","Unable to unlock pixels");
        goto exit;
    }

    if (0<frameSize)
    {
        isFrameRead = JNI_TRUE;
    }

    exit:
    return isFrameRead;

}

