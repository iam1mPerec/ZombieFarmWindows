#include <iostream>
#include "DeBuff.h"

using namespace std;

deBuff::deBuff():
stun(0),
bleedDmg(0),
bleedCount(0)
{
    
}

int deBuff::getBleed() const
{
    return bleedDmg;
}

int deBuff::getBleedCount() const
{
    return bleedCount;
}

int deBuff::getStun() const
{
    return stun;
}

void deBuff::setBleeding(const int DMG, const int COUNT)
{
    bleedDmg = DMG;
    bleedCount = COUNT;
}

void deBuff::setStunned(const int Stun)
{
    stun = Stun;
}

void deBuff::bleedOut()
{
    --bleedCount;
    
    if (bleedCount <= 0)
    {
        bleedDmg = 0;
        bleedCount = 0;
    }
}

void deBuff::BeStunned()
{
    if (stun)
    {
        stun--;
    }
}