#pragma once
#include "equipment.h"

class chest : public equipment
{
    const int def;
    const int hp;
public:
chest(const int Def,const int Hp,const int Price, const int Restriction);
    
    int getDef()      const;
    int getHp()       const;
};