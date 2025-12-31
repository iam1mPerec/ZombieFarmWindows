#include <iostream>
#include "Abilities.h"

using namespace std;

abilities::abilities() : UnUsedPoints(0),
                         Ability_1(0),
                         Ability_2(0),
                         Ability_3(0),
                         Ability_4(0),
                         Ability_5(0),
                         MaxLvl(5)
{
}

void abilities::lvlUpAbility(const int ability)
{
    if (UnUsedPoints)
    {
        switch (ability)
        {
        case 1:
            if (Ability_1 < MaxLvl)
            {
                Ability_1++;
            }
            else
            {
                UnUsedPoints++;
            }
            break;
        case 2:
            if (Ability_2 < MaxLvl)
            {
                Ability_2++;
            }
            else
            {
                UnUsedPoints++;
            }
            break;
        case 3:
            if (Ability_3 < MaxLvl)
            {
                Ability_3++;
            }
            else
            {
                UnUsedPoints++;
            }
            break;
        case 4:
            if (Ability_4 < MaxLvl)
            {
                Ability_4++;
            }
            else
            {
                UnUsedPoints++;
            }
            break;
        case 5:
            if (Ability_5 < MaxLvl)
            {
                Ability_5++;
            }
            else
            {
                UnUsedPoints++;
            }
            break;

        default:
            break;
        }
        UnUsedPoints--;
    }
}

abilities::~abilities()
{
}

bool abilities::unUsedPoint() const
{
    return UnUsedPoints;
}

int abilities::getAbility(const int ability) const
{
    switch (ability)
    {
    case 1:
        return Ability_1;
    case 2:
        return Ability_2;
    case 3:
        return Ability_3;
    case 4:
        return Ability_4;
    case 5:
        return Ability_5;
    default:
        return 0;
    }
}

void abilities::addUnused()
{
    UnUsedPoints++;
}
void abilities::addUnused(const int count)
{
    if (count > 0)
    {
        UnUsedPoints += count;
    }
}