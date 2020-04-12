//
// Created by andy on 2020/4/12.
//

#ifndef NDKDEMO_CONCURRENT_H
#define NDKDEMO_CONCURRENT_H

#include <vector>
using namespace std;

class Concurrent {
public:
    Concurrent();
    ~Concurrent();
    void read();
    void write();
private:
    vector<char>* m_data;
};


#endif //NDKDEMO_CONCURRENT_H
