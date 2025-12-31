#pragma once
#include "consumables.h"

class grenade : public consumables
{
    const int Dmg;
    
public:
    grenade(const int Dmg, const int Count, const int Price);
    int  getProperty() const;
};