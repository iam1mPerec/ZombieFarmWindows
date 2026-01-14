#include <iostream>
#include "kit.h"

using namespace std;

kit::kit(const int Hp, const int Count, const int Price):
consumables(consume::kit, Count, Price),
hp(Hp)
{
    fillTitle("Kit");
}

int kit::getProperty() const
{
    return hp;
}