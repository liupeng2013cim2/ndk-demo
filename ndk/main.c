#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test.h"

int main() {
    printf("Hello, World!\n");

    unsigned short u11 = 2;
    printf("u11=%hu，占用字节数:%d\n", u11, sizeof(u11));

    short u12 = 2;
    printf("u12=%u，占用字节数:%d\n", u12, sizeof(u12));

    unsigned int u21 = 123;
    printf("u21=%u, 占用字节数:%d\n", u21, sizeof(u21));

    int u22 = -123;
    printf("u22=%d, 占用字节数:%d\n", u22, sizeof(u22));

    float f = -2.98F;
    printf("f=%f, 占用字节:%d\n", f, sizeof(f));

    char* s = "我是谁";
    printf("question is: %s\n", s);

    char buffer[200] ;
    sprintf(buffer, "char is %s", s);
    printf("buffer is %s, size is %d, strlen is %d\n", buffer, sizeof(buffer), strlen(buffer));

    char* dest = (char*)malloc(strlen(buffer)* sizeof(char));
    strcpy(dest, buffer);
    printf("%s\n", dest);

    char buffer2[strlen(buffer)];
    strcpy(buffer2, buffer);
    printf("%s\n", buffer2);
    printf("--\n");

    // 不赋值，则元素的值为随机的，不一定都是0
    int array[22] = {6};
    printf("array length: %d\n", sizeof(array) / sizeof(int));
    int len = sizeof(array) / sizeof(int);
    for (int i = 0; i < len; ++i) {
        printf("ele of %d is %d, 内存地址为 %#x\n", i, array[i], (array + i));
    }

    // 分配空间 并初始化，与malloc不同（不需初始化）
    int* p = calloc(10, sizeof(int));
    for (int j = 0; j < 10; ++j) {
        printf("第 %d 个元素为 %d, 内存地址为%#x\n", j, *(p + j), (p + j));
    }
    // 一定要释放
    free(p);

    // 分配空间，没有初始化
    char* str = (char*)malloc(10 * sizeof(char));
    // 初始化
    memset(str, 'a', 10 * sizeof(char));
    for (int j = 0; j < 10; ++j) {
        printf("第 %d 个元素为 %c, 内存地址为%#x\n", j, *(str + j), (str + j));
    }
    free(str);

    // 形参 指针
    int t = 1;
    int* pt = &t;
    add(pt);
    printf("t:%d\n", t);

    // 实参
    int t2 = 1;
    add2(t2);
    printf("t2:%d\n", t2);

    // 可变参数
    int src = 1;
    add3(&src, 2,5,3,2,4,3);
    printf("src:%d\n", src);

    // 函数指针 类似于面向对象的接口回调
    char* str1 = "kjdjfs";
    int(*getLength)(char*) = getLen;
    int len1 = print(getLength, str1);
    printf("len1:%d\n", len1);



    return 0;
}
