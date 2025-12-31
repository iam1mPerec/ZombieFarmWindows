#pragma once
#include "constructions.h"

class resources
{
    int space;
    int food;
    int wood;
    int seeds;
    int money;
    int init_x;
    int init_y;
    constructions &possession;
    
public:
    
    resources(constructions &possession);
    void addFood(const int ammount);
    void addWood(const int ammount);
    void addSeeds(const int ammount);
    void addMoney(const int ammount);
    void load(const int Wood, const int Food,const int Seeds,const int Money);
    int getFood() const;
    int getWood() const;
    int getSeeds() const;
    int getMoney() const;
    int getSpace() const;
    int getInit_x() const;
    int getInit_y() const;
    int getMax() const;
    void map(char** ar);
};