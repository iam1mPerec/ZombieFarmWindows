#include <iostream>
#include "Walker.h"

using namespace std;

walker::walker(const int lvl):
zombie(zombies::walker, lvl)
{
    atk    = 2*lvl+7;
    hp     = 10*lvl+100;
    deff   = lvl/3+1;
    type = zombies::walker;
    
    char array[3][11] =
    {
        "|  ___   |",
        "| (\7_\7)  |",
        "|  /_\\   |"
    };
    
    for (int j = 0; j<3; j++)
    {
        for (int i = 0; i<11; i++)
        {
            pic[j+3][i] = array[j][i];
        }
    }
    
    char name[] = {"Walker"};
    for (int i = 0; i<6; i++)
    {
        pic[1][1+i] = name[i];
    }
    
    draw();
    priority = 7;
}