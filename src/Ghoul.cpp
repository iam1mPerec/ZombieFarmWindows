#include <iostream>
#include "Ghoul.h"

using namespace std;

ghoul::ghoul(const int lvl):
zombie(zombies::ghoul, lvl)
{
    atk    = 10*lvl+20;
    hp     = 10*lvl+100;
    deff    = lvl/3+1;
    type = zombies::ghoul;
    
    char array[3][11] =
    {
        "|  ___   |",
        "| (\4_\5)  |",
        "|  /_\\   |"
    };
    
    for (int j = 0; j<3; j++)
    {
        for (int i = 0; i<11; i++)
        {
            pic[j+3][i] = array[j][i];
        }
    }
    
    char name[] = {"Ghoul"};
    for (int i = 0; i<5; i++)
    {
        pic[1][1+i] = name[i];
    }
    
    draw();
    priority = 9;
}