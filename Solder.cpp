#include <iostream>
#include "Solder.h"

using namespace std;

solder::solder():
unit(title::rookie)
{
    alive = true;
    create();
    lvl = 1;
    stat();
    hp = maxHp;
    draw();
}

solder::solder(const int LVL, const int HP):
unit(title::rookie)
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
    if (LVL == maxLVL)
    {
        abilities.addUnused();
    }
    draw();
}

void solder::create()
{
    priority = 9;
    maxLVL = 10;
    maxExp = 50;
    char troop[3][22] =
    {
        "|        ___        |",
        "|       (\2_\2)       |",
        "|        / \\        |"
    };
    for (int j = 0; j<3; j++)
    {
        for (int i = 0; i<22; i++)
        {
            pic[j+2][i] = troop[j][i];
        }
    }
    char name[] = {"Rookie"};
    for (int i = 0; i<6; i++)
    {
        pic[1][12+i] = name[i];
    }
}

void solder::stat()
{
    if (shilds)
    {
        deff = (lvl/3+1)*2;
    }
    else
    {
        deff = lvl/3+1;
    }
    atk    = 2*lvl+15;
    maxHp  = 10*lvl+100;
    maxExp = 50;
    for (int i = 1; i<lvl; i++)
    {
        maxExp *= 1.25;
    }
    maxTurns = 1;
    priority = 9;
    addBuff();
}
