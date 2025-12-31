#pragma once
#include "equipment.h"

class weapon : public equipment
{
    const int atk;
    
    const int turns;
    
    const int splashDmg;
    
    const int stun;
    
    const int bleed;
    
    const int crit;
    
public:
weapon(const int Atk, const int Turns, const int Crit, const int SplashDmg, const int Stun, const int bleed,
       const int Price, const int Restriction);
    
    int getDmg()       const;
    int getTurns()     const;
    int getCrit()      const;
    int getStun()      const;
    int getSplash()    const;
    int getPirs()      const;
};