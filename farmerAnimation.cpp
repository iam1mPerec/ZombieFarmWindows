#include <iostream>
#include "farmerAnimation.h"
#include "screen.h"

using namespace std;

farmerAnimation::farmerAnimation(char** M, field& MField, events_list& List, resources& res, dialogBox &dial):
Dial(dial),
list(List),
Res(res),
x1(0),
x2(0),
y1(0),
y2(0),
MyField(MField),
screen(M),
waiting(3),
tsup(chill),
visible(true),
back(false),
firstrun(false),
Y(x/2-4),
X(y/2+8),
w8(6),
ch(' '),
plant(potato),
farmboy(nullptr)
{
}

void farmerAnimation::hide()
{
    visible = false;
    screen[Y][X] = ' ';
}

void farmerAnimation::reveal()
{
    visible = true;
    
    if(ch=='|')
    {
        ch = ' ';
    }
}

void farmerAnimation::createSector()
{
    int s = MyField.getSize()*2 - 1;
    char** M = new char* [s];
    for (int i = 0; i<s; i++)
    {
        M[i] = new char [s];
    }
    
    for (int j = 0; j<s; j++)
    {
        for (int i = 0; i<s; i++)
        {
            M[j][i] = ' ';
        }
    }
    
    int Y1 = y1 - (BottomPlank/2 - MyField.getSize())-1;
    int Y2 = y2 - (BottomPlank/2 - MyField.getSize());
    int X1 = x1 - (SidePlank/2 - MyField.getSize())-1;
    int X2 = x2 - (SidePlank/2 - MyField.getSize());
                            
    if (visible)
    {
        plantSelector();
    }
    for (int j = Y1; j<Y2; j++)
    {
        for (int i = X1; i<X2; i++)
        {
            if (MyField.checkForPlace(j, i))
            {
                M[j][i] = '#';
            }
        }
    }
    list.AddPlant(MyField, M, s, Dial, plant);
    
    for (int i = 0; i<s; i++)
    {
        delete [] M[i];
    }
    delete [] M;
}

void farmerAnimation::resetVar()
{
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    Y = x/2-4;
    X = y/2+8;
    tsup = chill;
    waiting = 3;
    w8 = 6;
    plant = potato;
    firstrun = true;
    farmboy->free();
    back = false;
}

void farmerAnimation::seeder()
{
    if (x1>x2)
    {
        int b = x1;
        x1 = x2;
        x2 = b;
    }
    if (y1>y2)
    {
        int b = y1;
        y1 = y2;
        y2 = b;
    }
    
    for (int j = y1; j<y2+1; j++)
    {
        for (int i = x1; i<x2+1; i++)
        {
            if(screen[j][i] == ' ')
            {
                screen[j][i] = '.';
            }
        }
    }
}

void farmerAnimation::plantSelector()
{
    if (x1>x2)
    {
    int b = x1;
        x1 = x2;
        x2 = b;
    }
    if (y1>y2)
    {
    int b = y1;
        y1 = y2;
        y2 = b;
    }
    
    for (int j = y1; j<y2+1; j++)
    {
        for (int i = x1; i<x2+1; i++)
        {
            screen[j][i] = '*';
        }
    }
}

void farmerAnimation::glowing()
{
    waiting--;
    if (waiting == 0)
    {
        MyField.showField();
        waiting = 3;
    }
    else
    {
        plantSelector();
    }
}

void farmerAnimation::startCollecting(farmer* Farmboy)
{
    farmboy = Farmboy;
    tsup = action::gather;
    firstrun = true;
}

void farmerAnimation::startPlanting(const int X1, const int X2, const int Y1, const int Y2, enum plants Plant, farmer* Farmboy)
{
    farmboy = Farmboy;
    x1 = X1;
    x2 = X2;
    y1 = Y1;
    y2 = Y2;
    plant = Plant;
    tsup = action::plant;
    firstrun = true;
}

int farmerAnimation::getDone() const
{
    return tsup;
}

void farmerAnimation::show()
{
    if (tsup == action::gather)
    {
        if (firstrun)
        {
            farmboy->busy();
            firstrun = false;
        }
    if (Y != BottomPlank/2+MyField.getSize()+1 && !back)
    {
        if (visible)
        {
            screen[Y][X] = ch;
        }
        Y++;
        ch = screen[Y][X];
        if (visible)
        {
        screen[Y][X] = char(31);
        }
    }
    else
    {
        if (X != SidePlank/2 && !back)
        {
            if (visible)
            {
                screen[Y][X] = ch;
            }
            X--;
            ch = screen[Y][X];
            if (visible)
            {
            screen[Y][X] = char(31);
            }
        }
        else
        {
            if (visible)
            {
            MyField.openGates();
            }
            if (w8 != 0)
            {
                w8--;
            }
            else
            {
                while(list.getHead() && list.getHead()->show_progress())
                {
                    if (list.getHead()->getReward() > 0)
                    {
                        Res.addFood(list.getHead()->getReward()*list.getHead()->getAmmount());
                    }
                    else
                    {
                        Res.addSeeds(list.getHead()->getReward()*list.getHead()->getAmmount()*(-7));
                    }
                    list.deleteNode(list.getHead());
                }
                
                if (visible)
                {
                    MyField.showField();
                    MyField.closeGates();
                }
                back = true;
                
                if(X != y/2+8)
                {
                    if (visible)
                    {
                        screen[Y][X] = ch;
                    }
                    X++;
                    ch = screen[Y][X];
                    if (visible)
                    {
                    screen[Y][X] = char(31);
                    }
                }
                else
                {
                    if (Y != x/2-4)
                    {
                        if (visible)
                        {
                            screen[Y][X] = ch;
                        }
                        Y--;
                        ch = screen[Y][X];
                        if (visible)
                        {
                            screen[Y][X] = char(31);
                        }
                    }
                    else
                    {
                        screen[Y][X] = ' ';
                        farmboy->free();
                        resetVar();
                    }
                }
            }
        }
    }
}
    if (tsup == action::plant)
    {
        if (firstrun)
        {
            farmboy->busy();
            firstrun = false;
        }
        if (Y != BottomPlank/2+MyField.getSize()+1 && !back)
        {
            if (visible)
            {
                glowing();
            }
            screen[Y][X] = ch;
            Y++;
            ch = screen[Y][X];
            
            if (visible)
            {
                screen[Y][X] = char(31);
            }
        }
        else
        {
            if (X != SidePlank/2 && !back)
            {
                if (visible)
                {
                    glowing();
                }
                screen[Y][X] = ch;
                X--;
                ch = screen[Y][X];
                
                if (visible)
                {
                    screen[Y][X] = char(31);
                }
            }
            else
            {
                if (visible)
                {
                MyField.openGates();
                }
                if (w8 != 0)
                {
                    if (visible)
                    {
                        glowing();
                    }
                    w8--;
                }
                else
                {
                    if (visible)
                    {
                        MyField.showField();
                        seeder();
                        MyField.closeGates();
                    }
                    back = true;
                    
                    if(X != y/2+8)
                    {
                        if (visible)
                        {
                        screen[Y][X] = ch;
                        }
                        X++;
                        ch = screen[Y][X];
                        if (visible)
                        {
                            screen[Y][X] = char(31);
                        }
                    }
                    else
                    {
                        if (Y != x/2-4)
                        {
                            screen[Y][X] = ch;
                            Y--;
                            ch = screen[Y][X];
                            if (visible)
                            {
                                screen[Y][X] = char(31);
                            }
                        }
                        else
                        {
                            screen[Y][X] = ' ';
                            farmboy->free();
                            createSector();
                            resetVar();
                        }
                    }
                }
            }
        }
    }
}