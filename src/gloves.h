#pragma once
#include "equipment.h"

class gloves : public equipment
{
    const int def;
    const int hp;
public:
    gloves(const int Def,const int Hp,const int Price, const int Restriction);
    
    int getDef()      const;
    int getHp()       const;
};