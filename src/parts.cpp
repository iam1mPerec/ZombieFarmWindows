#include <iostream>
#include "parts.h"

using namespace std;

parts::parts(const Parts type, const int Price):
item(itemType::equipment, Price, 0),
part(type)
{
}

int parts::getPartType() const
{
    return part;
}