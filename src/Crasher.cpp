#include <iostream>
#include "Crasher.h"

using namespace std;

crasher::crasher(const int lvl):
zombie(zombies::crasher, lvl)
{
    atk    = 12*lvl+20;
    hp     = 15*lvl+30;
    deff    = lvl/3+1;
    type = zombies::crasher;
    
    char array[3][11] =
    {
        "|  ___   |",
        "| (\7_^)  |",
        "|(/-_-\\) |"
    };
    
    for (int j = 0; j<3; j++)
    {
        for (int i = 0; i<11; i++)
        {
            pic[j+3][i] = array[j][i];
        }
    }
    
    char name[] = {"Crasher"};
    for (int i = 0; i<7; i++)
    {
        pic[1][1+i] = name[i];
    }
    
    draw();
    priority = 4;
}