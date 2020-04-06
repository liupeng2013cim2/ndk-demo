#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test.h"

int main() {
    printf("Hello, World!\n");

    unsigned short u11 = 2;
    printf("u11=%hu��ռ���ֽ���:%d\n", u11, sizeof(u11));

    short u12 = 2;
    printf("u12=%u��ռ���ֽ���:%d\n", u12, sizeof(u12));

    unsigned int u21 = 123;
    printf("u21=%u, ռ���ֽ���:%d\n", u21, sizeof(u21));

    int u22 = -123;
    printf("u22=%d, ռ���ֽ���:%d\n", u22, sizeof(u22));

    float f = -2.98F;
    printf("f=%f, ռ���ֽ�:%d\n", f, sizeof(f));

    char* s = "����˭";
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

    // ����ֵ����Ԫ�ص�ֵΪ����ģ���һ������0
    int array[22] = {6};
    printf("array length: %d\n", sizeof(array) / sizeof(int));
    int len = sizeof(array) / sizeof(int);
    for (int i = 0; i < len; ++i) {
        printf("ele of %d is %d, �ڴ��ַΪ %#x\n", i, array[i], (array + i));
    }

    // ����ռ� ����ʼ������malloc��ͬ�������ʼ����
    int* p = calloc(10, sizeof(int));
    for (int j = 0; j < 10; ++j) {
        printf("�� %d ��Ԫ��Ϊ %d, �ڴ��ַΪ%#x\n", j, *(p + j), (p + j));
    }
    // һ��Ҫ�ͷ�
    free(p);

    // ����ռ䣬û�г�ʼ��
    char* str = (char*)malloc(10 * sizeof(char));
    // ��ʼ��
    memset(str, 'a', 10 * sizeof(char));
    for (int j = 0; j < 10; ++j) {
        printf("�� %d ��Ԫ��Ϊ %c, �ڴ��ַΪ%#x\n", j, *(str + j), (str + j));
    }
    free(str);

    // �β� ָ��
    int t = 1;
    int* pt = &t;
    add(pt);
    printf("t:%d\n", t);

    // ʵ��
    int t2 = 1;
    add2(t2);
    printf("t2:%d\n", t2);

    // �ɱ����
    int src = 1;
    add3(&src, 2,5,3,2,4,3);
    printf("src:%d\n", src);

    // ����ָ�� �������������Ľӿڻص�
    char* str1 = "kjdjfs";
    int(*getLength)(char*) = getLen;
    int len1 = print(getLength, str1);
    printf("len1:%d\n", len1);



    return 0;
}
