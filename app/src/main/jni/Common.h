//
// Created by zzz on 2019/1/10.
//
#pragma once

#include "../../../../../../../Android/sdk/ndk-bundle/sysroot/usr/include/jni.h"
#include <android/log.h>

#define  LOGI(tag,...)  __android_log_print(ANDROID_LOG_INFO,tag,__VA_ARGS__)

void ThrowException(
        JNIEnv *env,
        const char *className,
        const char *message
);
