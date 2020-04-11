#include <jni.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include "log.h"
#include "animal.h"
#include "Cat.h"

using namespace std;

void testLocalRef1(JNIEnv *env);

void testGlobalRef(JNIEnv *env);

void newString(JNIEnv *env);

void testWeakGlobalRef(JNIEnv *env);

jclass globalRef;
jclass weakGlobalRef;
jstring globalRefStr;
jobject weakGlobalRefStr;
JavaVM * javaVm;

extern "C" JNIEXPORT void JNICALL
Java_com_andy_ndkdemo_MainActivity_testClass(
        JNIEnv *env,
        jobject /* this */) {
    Animal* animal = new Animal("dog", true);
    animal->walk();
    animal->eat();

    Animal* son = new Animal("dog-son", true);
    son->eat();
    son->walk();
    animal->setSon(son);

    int eq = equals(*animal, *son);
    LOGD("animal - son : %d", eq);

    Animal* son1 = animal->getSon();
    son1->walk();
    son1->eat();

    delete animal;
    delete son;

    Cat* cat = new Cat("cat1", false, "red", 22.8f);
    cat->walk();
    cat->eat();
    delete cat;
}

extern "C" JNIEXPORT void JNICALL
Java_com_andy_ndkdemo_MainActivity_crash(JNIEnv *env,
                                                    jobject /* this */) {

//    env = 0;
    jclass cls = env->FindClass("java/lang/String");

}

extern "C" JNIEXPORT void JNICALL
Java_com_andy_ndkdemo_MainActivity_accessGlobal(JNIEnv *env,
                                                jobject /* this */) {
    if (JNI_FALSE == env->IsSameObject(globalRefStr, NULL)) {
        LOGD("globalRefStr is still alive"); // 弱全局引用指向的对象是局部变量，超出了作用域被释放
    } else {
        LOGD("globalRefStr is recycled");
    }
    if (globalRefStr) {
        const char *str = env->GetStringUTFChars(globalRefStr, NULL);
        LOGD("global str:%s", str);
    } else {
        LOGD("global str is NULL");
    }

}

extern "C" JNIEXPORT void JNICALL
Java_com_andy_ndkdemo_MainActivity_accessWeakGlobal(JNIEnv *env,
                                                    jobject /* this */) {

    env->DeleteWeakGlobalRef(weakGlobalRefStr);
    weakGlobalRefStr = NULL;

    if (JNI_FALSE == env->IsSameObject(weakGlobalRefStr, NULL)) {
        LOGD("weakGlobalRefStr is still alive"); // 弱全局引用指向的对象是局部变量，超出了作用域被释放
    } else {
        LOGD("weakGlobalRefStr is is recycled");
    }
    if (weakGlobalRefStr) {
//        const char* str = env->GetStringUTFChars(weakGlobalRefStr, NULL);
//        LOGD("weak global str:%s", str);
    } else {
        LOGD("weak global str is NULL");
    }


}

void * threadMethod(void* args) {
    LOGD("threadMethod");
    JNIEnv* env ;
    // 建立线程相关的JNIEnv, javaVM是各个线程共用的
    javaVm->AttachCurrentThread(&env, NULL);
    jcharArray  array = env->NewCharArray(10);
    jchar* chars = env->GetCharArrayElements(array, NULL);
    for (int i = 0; i < 10; ++i) {
        *(chars + i) = 'a' + i;
    }
    env->ReleaseCharArrayElements(array, chars,JNI_COMMIT);
    jclass stringCls = env->FindClass("java/lang/String");
    jmethodID constructor = env->GetMethodID(stringCls, "<init>","([C)V");
    jstring jstring1 = static_cast<jstring>(env->NewObject(stringCls, constructor, array));
    const char* cstr = env->GetStringUTFChars(jstring1, NULL);
    LOGD("CSTR:%s", cstr);
    javaVm->DetachCurrentThread();
    char* str = "jjjj";
    return str;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_andy_ndkdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_andy_ndkdemo_MainActivity_stringFromJava2(
        JNIEnv *env,
        jobject thiz/* this */,
        jstring string
) {
    weakGlobalRefStr = env->NewWeakGlobalRef(string);
}

extern "C" JNIEXPORT void JNICALL
Java_com_andy_ndkdemo_MainActivity_startNativeThread(
        JNIEnv *env,
        jobject thiz/* this */){

    env->GetJavaVM(&javaVm);
    LOGD("startNativeThread");
    pthread_t pthread;
  pthread_create(&pthread, NULL, threadMethod, NULL);
  void* ret ;
  // 第二个参数得到线程的返回值
  pthread_join(pthread, &ret);
  LOGD("ret value from thread:%s", ret);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_andy_ndkdemo_MainActivity_stringFromJava(
        JNIEnv *env,
        jobject thiz/* this */,
        jstring string
) {
//    int result = 100/0;
//    LOGD("result:%d", result);
//    globalRefStr = static_cast<jstring>(env->NewGlobalRef(string));
//    weakGlobalRefStr = static_cast<jstring>(env->NewWeakGlobalRef(string));
    jboolean isCopy;
    const char *cstr = env->GetStringUTFChars(string, &isCopy);
    printf("%s\n", cstr);
    LOGD("%s\n", cstr);
    LOGD2("andylog", "%s\n", cstr);
    __android_log_print(ANDROID_LOG_VERBOSE, "LOG", "ANDROID log is %s\n", cstr);
    std::string hello = "Hello from C++";
    LOGD("HELLO IS %s", hello.c_str());
    printf("hello:%s\n", hello.c_str());

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
    jstring str = env->NewStringUTF(cstr);
    env->CallVoidMethod(thiz, updateMethodId, str);

    // 数组访问及修改 （1）副本
    int array[4];
    int len = sizeof(array) / sizeof(int);
    jintArray array1 = env->NewIntArray(10);
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
    jint *nativeDirectoryArray = env->GetIntArrayElements(array2,
                                                          &isCopy2);
    LOGD("copy:%u\n", isCopy);
    // b.赋值
    for (int i = 0; i < 10; ++i) {
        *(nativeDirectoryArray + i) = i + 1;
    }
    for (int i = 0; i < 10; ++i) {
        LOGD("i=%d, ele=%d", i, *(nativeDirectoryArray + i));
    }
    //c.复制内容到java
    // 第三个参数 JNI_ABORT 不改变java数组数据 JNI_COMMIT或0 会复制到java数组
    env->ReleaseIntArrayElements(array2, nativeDirectoryArray, JNI_ABORT);
    // 不管哪种参数，都有数据
    for (int i = 0; i < 10; ++i) {
        LOGD("i=%d, ele=%d", i, *(nativeDirectoryArray + i));
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
//        env->ThrowNew(exceptionCls, "not null");
    }

    // 局部引用  原生方法返回时，自动释放，此处为显示释放
    env->DeleteLocalRef(exceptionCls);
    exceptionCls = NULL;

    testLocalRef1(env);
    testLocalRef1(env);

    testGlobalRef(env);
    newString(env); // ok

    env->DeleteGlobalRef(globalRef);
    // 避免野指针最好的方法就是，释放后置空
    globalRef = NULL;

    // 报错 globalRef已被delete
//    newString(env);

    if (globalRef != NULL) {
        LOGD("globalRef is not null");
    }

    testWeakGlobalRef(env);

    if (JNI_FALSE == env->IsSameObject(weakGlobalRef, NULL)) {
        LOGD("weakGlobalRef is still alive"); // 弱全局引用指向的对象是局部变量，超出了作用域被释放
    } else {
        LOGD("weakGlobalRef is recycled");
    }


    return env->NewStringUTF(hello.c_str());
}

void newString(JNIEnv *env) {
    jmethodID constructorId = env->GetMethodID(globalRef, "<init>", "([C)V");

    jcharArray elemArray = env->NewCharArray(10);
    jchar *chars = env->GetCharArrayElements(elemArray, NULL);
    for (int i = 0; i < 10; ++i) {
        *(chars + i) = '0' + i;
    }
    env->ReleaseCharArrayElements(elemArray, chars, JNI_COMMIT);
    jstring str1 = static_cast<jstring>(env->NewObject(globalRef, constructorId, elemArray));
    const char *cstr1 = env->GetStringUTFChars(str1, NULL);
    LOGD("1111str:%s", cstr1);
}

void testGlobalRef(JNIEnv *env) {
    jclass cls = env->FindClass("java/lang/String");
    globalRef = static_cast<jclass>(env->NewGlobalRef(cls));
}

void testWeakGlobalRef(JNIEnv *env) {
    jclass cls = env->FindClass("java/lang/String");
    weakGlobalRef = static_cast<jclass>(env->NewWeakGlobalRef(cls));
}

void testLocalRef1(JNIEnv *env) {
    static jclass sClass = NULL;
    static jmethodID sConstructorId = NULL;
    static int count = 1;
    LOGD("count:%d", count);
    if (sClass == NULL) {
        LOGD("static cls is null");
        sClass = env->FindClass("java/lang/String");
        sConstructorId = env->GetMethodID(sClass, "<init>", "([C)V");

        jcharArray elemArray = env->NewCharArray(10);
        jchar *chars = env->GetCharArrayElements(elemArray, NULL);
        for (int i = 0; i < 10; ++i) {
            *(chars + i) = '0' + i;
        }
        env->ReleaseCharArrayElements(elemArray, chars, JNI_COMMIT);
        jstring str = static_cast<jstring>(env->NewObject(sClass, sConstructorId, elemArray));
        const char *cstr = env->GetStringUTFChars(str, NULL);
        LOGD("str:%s ,count:%d", cstr, count);
    } else {
        LOGD("STATIC IS NOT NULL");

        // ERROR 第二次进来，可能报错，静态变量指向的局部对象超出作用域被释放了
        /**
        jcharArray  elemArray = env->NewCharArray( 10);
        jchar* chars = env->GetCharArrayElements(elemArray, NULL);
        for (int i = 0; i < 10; ++i) {
            *(chars + i) = '0' + i;
        }
        env->ReleaseCharArrayElements(elemArray, chars, JNI_COMMIT);
        jstring str = static_cast<jstring>(env->NewObject(sClass, sConstructorId, elemArray));
        const char* cstr = env->GetStringUTFChars(str, NULL);
        LOGD("str:%s ,count:%d", cstr, count);
         */
    }


    if (sClass != NULL) {
        LOGD("static cls is not null");
    } else {

    }
    count++;
}

