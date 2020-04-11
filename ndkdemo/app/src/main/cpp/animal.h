//
// Created by andy on 2020/4/11.
//

#ifndef NDKDEMO_ANIMAL_H
#define NDKDEMO_ANIMAL_H

class Animal
{
public:
    Animal(const char* name, bool sex);
    ~Animal();
    void setSon(Animal* son);
    Animal* getSon() const;
    void walk();
    void eat();
    bool sex();
    char* name() const;
private:
    char* m_name = NULL;
    bool m_sex;
    //Animal son; //error 嵌套 导致类型定义不完整 incomplete type
    Animal* m_son = NULL;
};

#endif //NDKDEMO_ANIMAL_H
