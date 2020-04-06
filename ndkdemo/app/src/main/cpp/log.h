//
// Created by andy on 2020/4/6.
//
#include <android/log.h>
#ifndef NDKDEMO_LOG_H
#define NDKDEMO_LOG_H

#define LOG_TAG "logtest"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGT(...) __android_log_print(ANDROID_LOG_INFO,"alert",__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define LOGD2(tag, ...) __android_log_print(ANDROID_LOG_DEBUG,tag,__VA_ARGS__)

#endif //NDKDEMO_LOG_H
