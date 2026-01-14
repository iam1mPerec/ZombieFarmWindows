#include <iostream>
#include "Basher.h"

using namespace std;

basher::basher(const int lvl):
zombie(zombies::basher, lvl)
{
    atk    = 3;
    hp     = 15*lvl+200;
    deff    = lvl/3+2;
    type = zombies::basher;
    
    char array[3][11] =
    {
        "|  ___   |",
        "| (\7_\7)  |",
        "|(/___\\) |"
    };
    
    for (int j = 0; j<3; j++)
    {
        for (int i = 0; i<11; i++)
        {
            pic[j+3][i] = array[j][i];
        }
    }
    
    char name[] = {"Basher"};
    for (int i = 0; i<6; i++)
    {
        pic[1][1+i] = name[i];
    }
    
    draw();
    priority = 5;
}
