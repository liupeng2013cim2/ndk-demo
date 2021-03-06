//
// Created by andy on 2020/4/11.
//
#include <string>
#include "animal.h"
#include "log.h"

using namespace std;

int equals(Animal &src, Animal &dest) {
    char* name1 = src.m_name;
    char* name2 = dest.m_name;
    if (!name1 && name2) {
        return -1;
    }
    if (name1 && !name2) {
        return 1;
    }
    if (name1 == name2) {
        return 0;
    }
    while(*name1 == *name2) {
        name1++;
        name2++;
    }
    return *name1 - *name2;




}


Animal::Animal(const char *name, bool sex) {
    m_name = new char[strlen(name) + 1];
    strcpy(m_name, name);
    m_sex = sex;

    LOGD( "构造函数 animal %s", m_name );
}

Animal::~Animal() {
    LOGD( "析构函数 animal %s", m_name );
    if(m_name) {
        free(m_name);
        m_name = NULL;
    }
    if (m_son) {
        delete m_son;
        m_son = NULL;
    }
}

void Animal::eat() {
    LOGD( "animal %s eat", m_name );
}

void Animal::walk() {
    LOGD( "animal %s walk", m_name );
}

char* Animal::name() const {
    return m_name;
}

bool Animal::sex() {
    return m_sex;
}


void Animal::setSon(Animal *son) {
    m_son = new Animal(son->name(), son->sex());
}

Animal* Animal::getSon() const {
    return m_son;
}