#pragma once
#include "consumables.h"

class potion : public consumables
{
    const int hp;
    
public:
    potion(const int Hp, const int Count, const int Price);
    int  getProperty() const;
};