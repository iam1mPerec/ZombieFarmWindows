#pragma once
#include "equipment.h"

class helmet : public equipment
{
    const int def;
    const int hp;
    const int priority;
public:
    helmet(const int Def,const int Hp, const int Priority,const int Price, const int Restriction);
    
    int getDef()      const;
    int getHp()       const;
    int getPriority() const;
};