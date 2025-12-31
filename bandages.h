#pragma once
#include "consumables.h"

class bandages : public consumables
{
    const int hp;
    
public:
    bandages(const int Hp, const int Count, const int Price);
    int  getProperty() const;
};