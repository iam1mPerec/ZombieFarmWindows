#include <iostream>
#include "Sniper.h"

using namespace std;

sniper::sniper():
unit(title::sniper)
{
    create();
    lvl = 1;
    stat();
    hp = maxHp;
    abilities.addUnused();
    draw();
}

sniper::sniper(const int LVL, const int HP):
unit(title::sniper)
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

void sniper::create()
{
    alive = true;
    priority = 10;
    maxLVL = 25;
    maxExp = 100;
    char troop[3][22] =
    {
        "|        ___        |",
        "|       (\2_\2)       |",
        "|       <t==T==-    |"
    };
    
    for (int j = 0; j<3; j++)
    {
        for (int i = 0; i<22; i++)
        {
            pic[j+2][i] = troop[j][i];
        }
    }
    char name[] = {"Sniper"};
    for (int i = 0; i<6; i++)
    {
        pic[1][12+i] = name[i];
    }
}

void sniper::stat()
{
    if (shilds)
    {
        deff   = (lvl/3+5)*2;
    }
    else
    {
        deff   = lvl/3+5;
    }
    atk    = 4*lvl+50;
    maxHp  = 10*lvl+200;
    maxExp = 100;
    for (int i = 1; i<lvl; i++)
    {
        maxExp *= 1.25;
    }
    maxTurns = 1;
    priority = 10;
    addBuff();
}