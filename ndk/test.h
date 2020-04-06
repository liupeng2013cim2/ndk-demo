//
// Created by andy on 2020/4/5.
//

#ifndef NDK_TEST_H
#define NDK_TEST_H

void add(int* p);
void add2(int i);

void add3(int* src, ...);

int getLen(char* str);

int print(int(*method)(char*), char* str);


#endif //NDK_TEST_H
