#include <iostream>
#include "Farmer.h"

using namespace std;

farmer::farmer():
business(false),
fellow(nullptr)
{
    
}

void farmer::busy()
{
    business = true;
}

void farmer::free()
{
    business = false;
}

bool farmer::getbusiness() const
{
    return business;
}