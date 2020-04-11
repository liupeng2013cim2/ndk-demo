//
// Created by andy on 2020/4/11.
//

#ifndef NDKDEMO_CAT_H
#define NDKDEMO_CAT_H

#include "animal.h"

class Cat: public Animal
{
public:
    Cat(const char* name, bool sex, const char* color, float weight);
    ~Cat();
    void weight(float weight);
    float weight();
    void color(const char* color);
    char* color()const ;
private:
    char* m_color;
    float m_weight;
};

#endif //NDKDEMO_CAT_H
