//
// Created by andy on 2020/4/12.
//

#ifndef NDKDEMO_CONCURRENT_H
#define NDKDEMO_CONCURRENT_H

#include <vector>
using namespace std;

class Concurrent {
public:
    static int myCount;
    static bool running;
    static pthread_mutex_t mutex;
    Concurrent();
    ~Concurrent();
    void read();
    void write();
    void finish();
    vector<int>* data();
private:
    vector<int>* m_data = nullptr;
};


#endif //NDKDEMO_CONCURRENT_H
