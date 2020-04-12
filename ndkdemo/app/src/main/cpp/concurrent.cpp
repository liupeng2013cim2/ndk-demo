//
// Created by andy on 2020/4/12.
//

#include <pthread.h>
#include "concurrent.h"
#include "log.h"

int Concurrent::myCount = 1;
bool Concurrent::running = true;
pthread_mutex_t Concurrent::mutex; // 是数据，而不是指针
void* writeData(void* args){
    Concurrent* concurrent = (Concurrent*) args;
    vector<int>* data = concurrent->data();
    while(Concurrent::running) {
        begin:
        int ret = pthread_mutex_lock(&Concurrent::mutex);
        while(data->size() > 10) {
            LOGD("write, size is over 10");
            pthread_mutex_unlock(&Concurrent::mutex);
            goto begin;
        }
        Concurrent::myCount++;
        LOGD("write, push %d", Concurrent::myCount);
        data->push_back(Concurrent::myCount);

        if (Concurrent::myCount >=100) {
            concurrent->finish();
        }
        pthread_mutex_unlock(&Concurrent::mutex);
    }
    return NULL;
}

void* readData(void* args) {
    Concurrent* concurrent = (Concurrent*) args;
    vector<int>* data = concurrent->data();
    while(Concurrent::running) {
      begin:
        int ret = pthread_mutex_lock(&Concurrent::mutex);
        while(data->empty()) {
            LOGD("read, size is empty");
            pthread_mutex_unlock(&Concurrent::mutex);
            goto begin;
        }
        int ele = data->back();
        LOGD("read, pop:%d", ele);
        data->pop_back();
        pthread_mutex_unlock(&Concurrent::mutex);
    }

    return NULL;
}

Concurrent::Concurrent() {
    LOGD("构造函数Concurrent");
    m_data = new vector<int>;
    pthread_mutex_init(&mutex, NULL);
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

    pthread_mutex_destroy(&Concurrent::mutex);
}

vector<int>* Concurrent::data() {
    return m_data;
}