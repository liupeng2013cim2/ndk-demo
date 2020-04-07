#include <jni.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include "log.h"

using namespace std;

extern "C" JNIEXPORT jstring JNICALL
Java_com_andy_ndkdemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_andy_ndkdemo_MainActivity_stringFromJava(
        JNIEnv* env,
        jobject thiz/* this */,
        jstring string
        ) {
    int result = 100/0;
    LOGD("result:%d", result);
    jboolean isCopy;
    const char * cstr = env->GetStringUTFChars(string, &isCopy);
    printf("%s\n", cstr);
    LOGD("%s\n", cstr);
    LOGD2("andylog", "%s\n", cstr);
    __android_log_print(ANDROID_LOG_VERBOSE,"LOG", "ANDROID log is %s\n", cstr);
    std::string hello = "Hello from C++";
    LOGD("HELLO IS %s", hello.c_str());
    printf("hello:%s\n",hello.c_str());

    // 获取指定对象的class对象
    jclass activityClassId = env->GetObjectClass(thiz);

    // 获取/设置java对象的属性值
    jfieldID jfieldId = env->GetFieldID(activityClassId, "mCount", "I");
    jint count = env->GetIntField(thiz, jfieldId);
    LOGD("count:%d", count);
    env->SetIntField(thiz, jfieldId, 10);

    // 调用java方法
    jmethodID updateMethodId = env->GetMethodID(activityClassId,
            "updateUi", "(Ljava/lang/String;)V");
    jstring  str = env->NewStringUTF(cstr);
    env->CallVoidMethod(thiz, updateMethodId, str);

    // 数组访问及修改 （1）副本
    int array[4] ;
    int len = sizeof(array)/ sizeof(int);
    jintArray  array1 = env->NewIntArray(10);
    // a.复制到副本中
    env->GetIntArrayRegion(array1, 0, len, array);
    // b.修改副本
    for (int i = 0; i < len; ++i) {
        array[i] = i;
    }
    // c.重新拷贝回来
    env->SetIntArrayRegion(array1, 0, len, array);

    // d.调用java方法，将数组传回
    jmethodID updateDataMehtodId = env->GetMethodID(activityClassId,
            "updateData", "([I)V");
    env->CallVoidMethod(thiz, updateDataMehtodId, array1);

    // 数组访问及修改（2） 直接指针法
    jintArray array2 = env->NewIntArray(10);
    jboolean isCopy2;
    // a.获取指针
    jint* nativeDirectoryArray = env->GetIntArrayElements(array2,
            &isCopy2);
    LOGD("copy:%u\n", isCopy);
    // b.赋值
    for (int i = 0; i < 10; ++i) {
        *(nativeDirectoryArray + i) = i + 1;
    }
    for (int i = 0; i < 10; ++i) {
        LOGD("i=%d, ele=%d", i,*(nativeDirectoryArray + i));
    }
    //c.复制内容到java
    // 第三个参数 JNI_ABORT 不改变java数组数据 JNI_COMMIT或0 会复制到java数组
    env->ReleaseIntArrayElements(array2, nativeDirectoryArray, JNI_ABORT);
    // 不管哪种参数，都有数据
    for (int i = 0; i < 10; ++i) {
        LOGD("i=%d, ele=%d", i,*(nativeDirectoryArray + i));
    }
    env->CallVoidMethod(thiz, updateDataMehtodId, array2);

    // 异常处理
    // 1.调用java方法 而抛出异常
    /*
    jmethodID throwMethod = env->GetMethodID(activityClassId, "throwException", "()V");
    LOGD("call throwMethod 111");
    env->CallVoidMethod(activityClassId, throwMethod);
    LOGD("call throwMethod 222");
    jthrowable ex = env->ExceptionOccurred();
    LOGD("ex....");
    if(ex != 0) {
        LOGD("ex:%d", ex);
        env->ExceptionClear();
        LOGD("exception : %s", ex);
    }
    */

    // 抛异常
    jclass exceptionCls = env->FindClass("java/lang/NullPointerException");
    if (exceptionCls != 0) {
        env->ThrowNew(exceptionCls, "not null");
    }


    return env->NewStringUTF(hello.c_str());
}

