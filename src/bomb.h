#pragma once
#include "consumables.h"

class bomb : public consumables
{
    const int Dmg;
    
public:
    bomb(const int Dmg, const int Count, const int Price);
    int  getProperty() const;
};