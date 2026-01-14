#include <iostream>
#include "equipment.h"
#include "weapon.h"

using namespace std;

weapon::weapon(const int Atk, const int Turns, const int Crit, const int SplashDmg,
               const int Stun, const int Pirs, const int Price, const int Restriction):
equipment(Price, Restriction),
atk(Atk),
crit(Crit),
turns(Turns),
splashDmg(SplashDmg),
stun(Stun),
pirs(Pirs)
{
    fillTitle("Weapon");
}

int  weapon::getDmg()       const
{
    return atk;
}
int  weapon::getTurns()     const
{
    return turns;
}
int  weapon::getCrit()      const
{
    return crit;
}
int  weapon::getStun()      const
{
    return stun;
}
int  weapon::getSplash()    const
{
    return splashDmg;
}
int  weapon::getPirs()      const
{
    return pirs;
}