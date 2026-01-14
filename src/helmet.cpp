#include <iostream>
#include "equipment.h"
#include "helmet.h"

using namespace std;

helmet::helmet(const int Def,const int Hp, const int Priority,const int Price,const int Restriction):
equipment(Price, Restriction),
def(Def),
hp(Hp),
priority(Priority)
{
    fillTitle("Helmet");
}

int helmet::getDef()      const
{
    return def;
}
int helmet::getHp()       const
{
    return hp;
}
int helmet::getPriority() const
{
    return priority;
}
