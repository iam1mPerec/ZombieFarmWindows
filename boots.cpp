#include <iostream>
#include "equipment.h"
#include "boots.h"

using namespace std;

boots::boots(const int Def,const int Hp,const int Price, const int Restriction):
equipment(Price, Restriction),
def(Def),
hp(Hp)
{
    fillTitle("Boots");
}

int  boots::getHp()      const
{
    return hp;
}

int  boots::getDef()      const
{
    return def;
}