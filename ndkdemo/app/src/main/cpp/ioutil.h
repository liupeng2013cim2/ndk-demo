//
// Created by andy on 2020/4/12.
//

#ifndef NDKDEMO_IOUTIL_H
#define NDKDEMO_IOUTIL_H

class IOUtil
{
public:
    static IOUtil* getInstance(); // 单例模式
    void copyFile(const char* from, const char* to);
private:
    IOUtil();
    ~IOUtil();
//    static IOUtil* instance = nullptr; // error 静态变量只能在类外初始化，最好在cpp中
    static IOUtil* instance;
};

#endif //NDKDEMO_IOUTIL_H
