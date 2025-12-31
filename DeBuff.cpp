#include <iostream>
#include "DeBuff.h"

using namespace std;

deBuff::deBuff():
stun(0),
bleed(0),
bleedCount(0)
{
    
}

int deBuff::getBleed() const
{
    return bleed;
}

int deBuff::getBleedCount() const
{
    return bleedCount;
}

int deBuff::getStun() const
{
    return stun;
}

void deBuff::setBleeding(const int Bleed, const int Count)
{
    bleed      = Bleed;
    bleedCount = Count;
}

void deBuff::setStunned(const int Stun)
{
    stun = Stun;
}

void deBuff::bleedOut()
{
    bleed--;
    
    if (bleed <= 0)
    {
        bleed = 0;
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