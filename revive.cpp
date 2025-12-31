#include <iostream>
#include "revive.h"

using namespace std;

revive::revive(const int Hp, const int Count, const int Price):
consumables(consume::revive, Count, Price),
hp(Hp)
{
    fillTitle("Revive");
}

int revive::getProperty() const
{
    return hp;
}