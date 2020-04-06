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
    jboolean isCopy;
    const char * cstr = env->GetStringUTFChars(string, &isCopy);
    printf("%s\n", cstr);
    LOGD("%s\n", cstr);
    LOGD2("andylog", "%s\n", cstr);
    __android_log_print(ANDROID_LOG_VERBOSE,"LOG", "ANDROID log is %s\n", cstr);
    std::string hello = "Hello from C++";
    LOGD("HELLO IS %s", hello.c_str());
    printf("hello:%s\n",hello.c_str());

    // 调用java方法
    jclass activityClassId = env->GetObjectClass(thiz);
    jmethodID updateMethodId = env->GetMethodID(activityClassId,
            "updateUi", "(Ljava/lang/String;)V");
    jstring  str = env->NewStringUTF(cstr);
    env->CallVoidMethod(thiz, updateMethodId, str);

    // 数组
    int array[4] ;
    jintArray  array1 = env->NewIntArray(10);
    // 复制到副本中
    env->GetIntArrayRegion(array1, 0, 4, array);
    // 修改副本
    for (int i = 0; i < 4; ++i) {
        array[i] = i;
    }
    // 重新拷贝回来
    env->SetIntArrayRegion(array1, 0, 4, array);

    // 调用java方法，将数组传回
    jmethodID updateDataMehtodId = env->GetMethodID(activityClassId,
            "updateData", "([I)V");
    env->CallVoidMethod(thiz, updateDataMehtodId, array1);

    return env->NewStringUTF(hello.c_str());
}

