#include <iostream>
#include "Skills.h"

using namespace std;

Skills::Skills():
splashDmg(0),
stun(0),
stunCount(1),
crit(0),
critDmg(150),
pirs(0),
bleedCount(3)
{
    
}

void Skills::addSkills(const int SplashDmg, const int Stun, const int StunCount,
                       const int Pirs, const int BleedCount, const int Crit, const int CritDmg)
{
    splashDmg += SplashDmg;
    
    stun      += Stun;
    stunCount   += StunCount;
    
    crit      += Crit;
    critDmg   += CritDmg;
    
    pirs      += Pirs;
    bleedCount  += BleedCount;
}

void Skills::setSplashDmg(const int SplashDmg)
{
    splashDmg += SplashDmg;
}
void Skills::setStunChance(const int Stun)
{
    stun      += Stun;
}
void Skills::setCritChance(const int Crit)
{
    crit      += Crit;
}
void Skills::setPirsDmg(const int PirsDmg)
{
    pirs      += PirsDmg;
}

int Skills::getSplash() const
{
    return splashDmg;
}
int Skills::getStun() const
{
    return stun;
}
int Skills::getPirs() const
{
    return pirs;
}
int Skills::getCrit() const
{
    return crit;
}

int Skills::crited() const
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

int Skills::stuned() const
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
            return stunCount;
        }
        else
        {
            return 0;
        }
    }
}
