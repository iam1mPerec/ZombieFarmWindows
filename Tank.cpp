#include <iostream>
#include "Tank.h"

using namespace std;

tank::tank():
unit(title::tank)
{
    alive = true;
    create();
    lvl = 1;
    stat();
    hp = maxHp;
    abilities.addUnused();
    draw();
}

tank::tank(const int LVL, const int HP):
unit(title::tank)
{
    alive = true;
    create();
    lvl = LVL;
    if (lvl > maxLVL)
    {
        lvl = maxLVL;
    }
    stat();
    hp  = HP;
    if (hp > maxHp)
    {
        hp = maxHp;
    }
    abilities.addUnused(LVL);
    draw();
}

void tank::create()
{
    priority = 8;
    maxLVL = 25;
    maxExp = 100;
    char troop[3][22] =
    {
        "|        ___        |",
        "|       (\2_\2)       |",
        "|       <|  |>      |"
    };
    for (int j = 0; j<3; j++)
    {
        for (int i = 0; i<22; i++)
        {
            pic[j+2][i] = troop[j][i];
        }
    }
    char name[] = {"Tank"};
    for (int i = 0; i<4; i++)
    {
        pic[1][12+i] = name[i];
    }
}

void tank::stat()
{
    if (shilds)
    {
        deff    = (lvl*2+8)*2;
    }
    else
    {
        deff   = lvl*2+8;
    }
    atk    = 2.5*lvl+35;
    maxHp  = 25*lvl+300;
    maxExp = 100;
    for (int i = 1; i<lvl; i++)
    {
        maxExp *= 1.25;
    }
    maxTurns = 1;
    priority = 8;
    addBuff();
}