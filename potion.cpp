#include <iostream>
#include "potion.h"

using namespace std;

potion::potion(const int Hp, const int Count, const int Price):
consumables(consume::potion,Count,Price),
hp(Hp)
{
    fillTitle("Potion");
}

int potion::getProperty() const
{
    return hp;
}