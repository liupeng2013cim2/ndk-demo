//
// Created by andy on 2020/4/12.
//
#include <ostream>
#include <fstream>
#include "ioutil.h"
#include "log.h"

using namespace std;

//IOUtil::instance = nullptr; // errror 需要指明类型
IOUtil *IOUtil::instance = nullptr;

IOUtil::IOUtil() {
    LOGD("IOUtils 构造函数");
}

IOUtil::~IOUtil() {
    LOGD("IOUtils 析构函数");
}

IOUtil *IOUtil::getInstance() {
    if (instance) {
        return instance;
    } else {
        instance = new IOUtil();
        return instance;
    }
}

void IOUtil::copyFile(const char *from, const char *to) {
    LOGD("FROM:%s, TO:%s", from, to);
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    ifstream is;
    is.open(from);
    ofstream os;
    os.open(to);
    if (is.fail() || os.fail()) {
        LOGD("open file fail");
        goto exit;
    }
//    const int BUFFER_SIZE = 1024; // error 这里定义会报错，goto语句
//    char buffer[BUFFER_SIZE];
    while (!is.eof()) {
        is.getline(buffer, BUFFER_SIZE);
        LOGD("%s", buffer);
        os.operator<<(buffer);
    }
    exit:
        is.close();
        os.close();
}