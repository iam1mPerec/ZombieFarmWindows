#include <iostream>
#include "bomb.h"

using namespace std;

bomb::bomb(const int dmg, const int Count, const int Price):
consumables(consume::bomb, Count, Price),
Dmg(dmg)
{
    fillTitle("Bomb");
}

int bomb::getProperty() const
{
    return Dmg;
}