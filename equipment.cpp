#include <iostream>
#include "equipment.h"

using namespace std;

equipment::equipment(const int Price,const int restriction):
item(itemType::equipment, Price, restriction)
{
}

int equipment::getRestriction() const
{
    return restriction;
}
