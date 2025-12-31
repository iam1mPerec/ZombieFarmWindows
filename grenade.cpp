#include <iostream>
#include "grenade.h"

using namespace std;

grenade::grenade(const int dmg, const int Count, const int Price):
consumables(consume::grenade, Count, Price),
Dmg(dmg)
{
    fillTitle("Grenade");
}

int grenade::getProperty() const
{
    return Dmg;
}