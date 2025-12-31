#include <iostream>
#include "equipment.h"
#include "gloves.h"

using namespace std;

gloves::gloves(const int Def,const int Hp,const int Price, const int Restriction):
equipment(Price, Restriction),
def(Def),
hp(Hp)
{
    fillTitle("Gloves");
}

int  gloves::getHp()      const
{
    return hp;
}

int  gloves::getDef()      const
{
    return def;
}