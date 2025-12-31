#include <iostream>
#include "resources.h"

using namespace std;

resources::resources(constructions &possession):
wood(2000),
food(400),
seeds(100),
money(200),
possession(possession),
space(12),
init_x(3),
init_y(2)
{
    
}

void resources::load(const int Wood, const int Food,const int Seeds,const int Money)
{
    food = Food;
    wood = Wood;
    seeds = Seeds;
    money = Money;
}

void resources::addFood(const int ammount)
{
    food +=ammount;
    if (food>possession.getTentSize())
    {
        food = possession.getTentSize();
    }
}
void resources::addWood(const int ammount)
{
    wood +=ammount;
    if (wood>possession.getTentSize())
    {
        wood = possession.getTentSize();
    }
}
void resources::addSeeds(const int ammount)
{
    seeds +=ammount;
    if (seeds>possession.getTentSize())
    {
        seeds = possession.getTentSize();
    }

}

void resources::addMoney(const int ammount)
{
    money +=ammount;
    if (money>possession.getTentSize())
    {
        money = possession.getTentSize();
    }
}

int resources::getFood() const
{
    return food;
}
int resources::getWood() const
{
    return wood;
}
int resources::getSeeds() const
{
    return seeds;
}
int resources::getMoney() const
{
    return money;
}

int resources::getSpace() const
{
    return space;
}

int resources::getInit_x() const
{
    return init_x;
}
int resources::getInit_y() const
{
    return init_y;
}

int resources::getMax() const
{
    return possession.getTentSize();
}
