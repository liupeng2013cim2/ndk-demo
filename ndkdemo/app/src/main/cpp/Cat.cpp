//
// Created by andy on 2020/4/11.
//

#include <string>
#include "animal.h"
#include "Cat.h"
#include "log.h"

Cat::Cat(const char *name, bool sex, const char *color, float weight): Animal(name, sex) {
    m_color = new char[strlen(color) + 1];
    strcpy(m_color, color);
    m_weight = weight;
}

Cat::~Cat() {
    if(m_color) {
        free(m_color);
    }
    LOGD("CAT 析构 %s", name());
}

float Cat::weight() {
    return m_weight;
}

void Cat::weight(float weight) {
    m_weight = weight;
}

void Cat::color(const char *color) {
    m_color = new char[strlen(color) + 1];
    strcpy(m_color, color);
}

char* Cat::color() const {
    return m_color;
}

