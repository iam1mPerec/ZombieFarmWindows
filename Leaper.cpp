#include <iostream>
#include "Leaper.h"

using namespace std;

leaper::leaper(const int lvl):
zombie(zombies::leaper, lvl)
{
    atk    = 3*lvl+7;
    hp     = 10*lvl+100;
    deff    = lvl/3+1;
    type = zombies::leaper;
    
    char array[3][11] =
    {
        "|  ___   |",
        "| (\4_\5)  |",
        "| (__)   |"
    };
    
    for (int j = 0; j<3; j++)
    {
        for (int i = 0; i<11; i++)
        {
            pic[j+3][i] = array[j][i];
        }
    }
    
    char name[] = {"Leaper"};
    for (int i = 0; i<6; i++)
    {
        pic[1][1+i] = name[i];
    }
    
    draw();
    priority = 10;
}