//
// Created by zzz on 2019/1/14.
//
extern "C"{
#include <avilib.h>
}

#include <GLES/gl.h>
#include <GLES/glext.h>
#include <malloc.h>

#include "Common.h"
#include "test_zml_com_myndk_OpenGLPlayerActivity.h"

struct Instance
{
    char* buffer;
    GLuint texture;
    Instance():
            buffer(0),
            texture(0)
    {

    }
};

/*
 * Class:     test_zml_com_myndk_OpenGLPlayerActivity
 * Method:    init
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_test_zml_com_myndk_OpenGLPlayerActivity_init
        (JNIEnv *env, jclass clzz, jlong avi)
{
    Instance* instance = 0;
    long frameSize = AVI_frame_size((avi_t*) avi,1);
    if (0>=frameSize)
    {
        ThrowException(env,"java/io/RuntimeException","Unable to get the frame size.");
        goto exit;
    }
    instance = new Instance();
    if (0 == instance)
    {
        ThrowException(env,"java/RuntimeException","Unable to allocate instance.");
        goto exit;
    }

    instance->buffer = (char*)malloc(frameSize);
    if (0 == instance->buffer)
    {
        ThrowException(env,"java/io/RuntimeException","Unable to allocate buffer.");
        delete instance;
        goto exit;
    }

    exit:
    return (jlong) instance;
}

/*
 * Class:     test_zml_com_myndk_OpenGLPlayerActivity
 * Method:    initSurface
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_test_zml_com_myndk_OpenGLPlayerActivity_initSurface
        (JNIEnv *env, jclass clzz, jlong inst, jlong avi)
{
    Instance* instance = (Instance*) inst;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1,&instance->texture);
    /*绑定到生成的纹理上*/
    glBindTexture(GL_TEXTURE_2D,instance->texture);

    int  frameWidth = AVI_video_width((avi_t*)avi);
    int  frameHeight = AVI_video_height((avi_t*)avi);
    /*剪切纹理矩形*/
    GLint rect[] = {0,frameHeight,frameWidth,-frameHeight};
    glTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_CROP_RECT_OES,rect);

    /*填充颜色*/
    glColor4f(1.0,1.0,1.0,1.0);

    /*生成一个空的纹理*/
    glTexImage2D(GL_TEXTURE_2D,
                    0,
                    GL_RGB,
                    frameWidth,
                    frameHeight,
                    0,
                    GL_RGB,
                    GL_UNSIGNED_SHORT_5_6_5,
                    0);

}

/*
 * Class:     test_zml_com_myndk_OpenGLPlayerActivity
 * Method:    render
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_test_zml_com_myndk_OpenGLPlayerActivity_render
        (JNIEnv *env, jclass clzz, jlong inst, jlong avi)
{
    Instance* instance = (Instance*) inst;
    jboolean isFrameRead = JNI_FALSE;
    int keyFrame = 0;

    /*将AVI帧字节读到bitmap*/
    long frameSize = AVI_read_frame((avi_t*) avi,instance->buffer,&keyFrame);
    if (0 >= frameSize)
    {
        goto exit;
    }
    isFrameRead = JNI_TRUE;

    /*使用新帧更新纹理*/
    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    0,
                    0,
                    AVI_video_width((avi_t*) avi),
                    AVI_video_height((avi_t*) avi),
                    GL_RGB,
                    GL_UNSIGNED_SHORT_5_6_5,
                    instance->buffer);

    /*绘制纹理*/ //使用该函数，需要 启用GL ext原库.
    glDrawTexiOES(0,0,0,
                AVI_video_width((avi_t*)avi),
                AVI_video_height((avi_t*)avi));

    exit:
    return isFrameRead;
}

/*
 * Class:     test_zml_com_myndk_OpenGLPlayerActivity
 * Method:    free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_test_zml_com_myndk_OpenGLPlayerActivity_free
        (JNIEnv *env, jclass clzz, jlong inst)
{
    Instance* instance = (Instance*) inst;
    if (0!=instance)
    {
        free(instance->buffer);
        delete instance;
    }
}

