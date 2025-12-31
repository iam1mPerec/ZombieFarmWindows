#include <iostream>
#include "Lurker.h"

using namespace std;

lurker::lurker(const int lvl):
zombie(zombies::lurker, lvl)
{
    atk    = 3*lvl+10;
    hp     = 10*lvl+50;
    deff    = lvl/3+1;
    type = zombies::lurker;
   
    char array[3][11] =
    {
        "|  ___   |",
        "| (\7_\3)  |",
        "| <|_|>  |"
    };
    
    for (int j = 0; j<3; j++)
    {
        for (int i = 0; i<11; i++)
        {
            pic[j+3][i] = array[j][i];
        }
    }
    
    char name[] = {"Lurker"};
    for (int i = 0; i<6; i++)
    {
        pic[1][1+i] = name[i];
    }
    
    draw();
    priority = 8;
}