#pragma once
#include "consumables.h"

class revive : public consumables
{
    const int hp;
    
public:
    revive(const int Hp, const int Count, const int Price);
    int  getProperty() const;
};