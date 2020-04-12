//
// Created by andy on 2020/4/12.
//
/** 关键api  类似于java 可重入锁
std::__libcpp_thread_sleep_for(std::chrono::nanoseconds(100)); // 线程睡眠
std::mutex mutex1; // 锁
std::unique_lock<std::mutex> lock1(mutex1); // 独占锁

std::lock_guard<std::mutex> lock2(mutex1); // 另外一种锁 有生命范围 类似于synchroinzed
std::condition_variable full_condition; // 锁的条件变量 类似于可重入锁的condition
 */

#include <pthread.h>
#include "concurrent.h"
#include "log.h"

using namespace std;

int Concurrent::myCount = 0;
bool Concurrent::running = true;
mutex Concurrent::mutex; // 是数据，而不是指针
condition_variable Concurrent::full_condition;
condition_variable Concurrent::empty_condition;
const int MAX_SHARE_COUNT = 1;
const int MAX_COUNT = 10;

void* writeData(void* args){
    Concurrent* concurrent = (Concurrent*) args;
    vector<int>* data = concurrent->data();
    while(Concurrent::running) {
        unique_lock<std::mutex> lock(Concurrent::mutex);
        LOGD("WRIET SIZE: %d", data->size());
        while(data->size() >= MAX_SHARE_COUNT) {
            LOGD("write, size is over %d", MAX_SHARE_COUNT);
            Concurrent::full_condition.wait(lock);
        }

        LOGD("write, push %d", Concurrent::myCount);
        data->push_back(Concurrent::myCount);
        Concurrent::myCount++;

        if (Concurrent::myCount >= MAX_COUNT) {
            concurrent->finish();
        }
        Concurrent::empty_condition.notify_all();
        lock.unlock();
    }
    LOGD("wriet over");
    return NULL;
}

void* readData(void* args) {
    Concurrent* concurrent = (Concurrent*) args;
    vector<int>* data = concurrent->data();
    while(Concurrent::running) {
        unique_lock<std::mutex> lock(Concurrent::mutex);
        while(data->empty()) {
            LOGD("read, size is empty");
            Concurrent::empty_condition.wait(lock);
        }
        int ele = data->back();
        LOGD("read, pop:%d", ele);
        data->pop_back();
        Concurrent::full_condition.notify_all();
        lock.unlock();
    }
    LOGD("read over");
    return NULL;
}

Concurrent::Concurrent() {
    LOGD("构造函数Concurrent");
    m_data = new vector<int>;
    m_data->clear();
}

Concurrent::~Concurrent() {
    LOGD("析构函数 Concurrent");
}

void Concurrent::read() {
    LOGD("read");
    pthread_t pthread;
    pthread_create(&pthread, NULL,readData,this);
}

void Concurrent::write() {
    LOGD("write");

    pthread_t pthread;
    pthread_create(&pthread, NULL,writeData,this);
}

void Concurrent::finish() {
    running = false;
}

vector<int>* Concurrent::data() {
    return m_data;
}