//
// Created by andy on 2020/4/12.
//

#include "concurrent.h"
#include "log.h"

Concurrent::Concurrent() {
    LOGD("构造函数Concurrent");
}

Concurrent::~Concurrent() {
    LOGD("析构函数 Concurrent");
}

void Concurrent::read() {
    LOGD("read");
}

void Concurrent::write() {
    LOGD("write");
}