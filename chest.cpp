#include <iostream>
#include "equipment.h"
#include "chest.h"

using namespace std;

chest::chest(const int Def,const int Hp,const int Price, const int Restriction):
equipment(Price, Restriction),
def(Def),
hp(Hp)
{
    fillTitle("Chest");
}

int  chest::getHp()      const
{
    return hp;
}

int  chest::getDef()      const
{
    return def;
}