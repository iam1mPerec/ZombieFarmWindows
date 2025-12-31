#include <iostream>
#include "bandages.h"

using namespace std;

bandages::bandages(const int Hp, const int Count, const int Price):
hp(Hp),
consumables(consume::bandages, Count, Price)
{
    fillTitle("Bandages");
}

int bandages::getProperty() const
{
    return hp;
}