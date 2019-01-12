#include<jni.h>
#include <android/log.h>

#include "test_zml_com_myndk_JNITest.h"

#define LOG_TAG "ZMLIANG"
#define  LOG(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

JNIEXPORT jstring JNICALL Java_test_zml_com_myndk_JNITest_getVersion(JNIEnv *env, jclass clz)
{
    return (*env)->NewStringUTF(env, "This is NDK String version 1.0.0");
}

JNIEXPORT jstring JNICALL Java_test_zml_com_myndk_JNITest_sendMessage(JNIEnv *env, jclass clz, jstring msg)
{
    jboolean isCopy;
    const char* str;
    str = (char*)(*env)->GetStringUTFChars(env,msg,&isCopy);
    if (0!=str)
    {
        LOG("接收到的: %s",str);
        (*env)->ReleaseStringUTFChars(env,msg,*str);
        if (isCopy == JNI_TRUE)
        {
            return (*env)->NewStringUTF(env,"是复制的");
        }
        else
        {
            return (*env)->NewStringUTF(env,"不是复制的");
        }
    }
    return "没收到消息";
}