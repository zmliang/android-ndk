#include "source/transcode/import/v4l/videodev2.h"

//
// Created by zzz on 2019/1/10.
//
extern "C"{
#include <avilib.h>
}

#include "Common.h"
#include "test_zml_com_myndk_AbstractPlayerActivity.h"

JNIEXPORT jlong JNICALL Java_test_zml_com_myndk_AbstractPlayerActivity_open
        (JNIEnv *env, jclass clz, jstring fileName)
{
    avi_t* avi = 0;
    const char* cFileName = (env)->GetStringUTFChars(fileName,0);
    if (0 == cFileName)
    {
        goto exit;
    }
    avi = AVI_open_input_file(cFileName,1);
    env->ReleaseStringUTFChars(fileName,cFileName);

    if (0 == avi)
    {
        ThrowException(env,"java/io/IOException",AVI_strerror());
    }

    exit:
    return (jlong)avi;
}

JNIEXPORT jint JNICALL Java_test_zml_com_myndk_AbstractPlayerActivity_getWidth
        (JNIEnv *env, jclass clzz, jlong avi)
{
    return AVI_video_width((avi_t*)avi);
}


JNIEXPORT jint JNICALL Java_test_zml_com_myndk_AbstractPlayerActivity_getHeight
        (JNIEnv *env, jclass clazz, jlong avi)
{
    return AVI_video_height((avi_t*) avi);
}


JNIEXPORT jdouble JNICALL Java_test_zml_com_myndk_AbstractPlayerActivity_getFrameRate
        (JNIEnv *env, jclass clazz, jlong avi)
{
    return AVI_frame_rate((avi_t*) avi);
}
JNIEXPORT void JNICALL Java_test_zml_com_myndk_AbstractPlayerActivity_close
        (JNIEnv *env, jclass clazz, jlong avi)
{
    AVI_close((avi_t*) avi);
}
