//
// Created by andy on 2020/4/5.
//
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "test.h"

void add(int * p) {
    (*p)++;
    printf("add, *p=%d\n", *p);
}

void add2(int i) {
    i++;
    printf("add, i=%d\n", i);

}

void add3(int* src,...) {

    va_list changList;
    va_start(changList, src);
    for (int i = 0; i <3 ; ++i) {
        int item = va_arg(changList, int);
        *src += item;
    }
    va_end(changList);

}

int getLen(char *s) {
    return strlen(s);
}


int print(int(*method_p)(char*), char* str) {
    int len = method_p(str);
    printf("call method:%s\n",method_p);
    return len;
}

