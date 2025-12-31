#include <iostream>
#include "Skills.h"

using namespace std;

skills::skills():
splashDmg(0),
stun(0),
stunDur(1),
crit(0),
critDmg(150),
pirs(0),
bleedDur(3)
{
    
}

void skills::addSkills(const int SplashDmg, const int Stun, const int StunDur,
                       const int Pirs, const int BleedDur, const int Crit, const int CritDmg)
{
    splashDmg += SplashDmg;
    
    stun      += Stun;
    stunDur   += StunDur;
    
    crit      += Crit;
    critDmg   += CritDmg;
    
    pirs      += Pirs;
    bleedDur  += BleedDur;
}

void skills::setSplashDmg(const int SplashDmg)
{
    splashDmg += SplashDmg;
}
void skills::setStunChance(const int Stun)
{
    stun      += Stun;
}
void skills::setCritChance(const int Crit)
{
    crit      += Crit;
}
void skills::setPirsDmg(const int Pirs)
{
    pirs      += Pirs;
}

int skills::getSplash()   const
{
    return splashDmg;
}
int skills::getStun()     const
{
    return stun;
}
int skills::getPisrs()    const
{
    return pirs;
}
int skills::getCrit()     const
{
    return crit;
}

int skills::crited() const
{
    if (!crit)
    {
        return 0;
    }
    else
    {
        srand(unsigned(time(NULL)));
        int chance = rand()%101 + 1;
        if (chance <= crit)
        {
            return critDmg;
        }
        else
        {
            return 0;
        }
    }
}

int skills::stuned() const
{
    if (!stun)
    {
        return 0;
    }
    else
    {
        srand(unsigned(time(NULL)));
        int chance = rand()%101 + 1;
        if (chance <= stun)
        {
            return stunDur;
        }
        else
        {
            return 0;
        }
    }
}

int skills::setBleading() const
{
    if (bleedDur)
    {
        return pirs;
    }
    else
    {
        return 0;
    }
}