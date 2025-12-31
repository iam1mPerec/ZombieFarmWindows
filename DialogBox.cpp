#include <iostream>
#include "dialogBox.h"
#include "screen.h"
#include "GMGameMenu.h"

dialogBox::dialogBox():
px(ScreenSize::x - BottomPlank),
py(SidePlank),
NumberOfLines(px/2)
{
    Box = new char * [px];
    for (int i = 0; i<px; i++)
    {
        Box[i] = new char [py];
    }
    clearBox();
}

void dialogBox::lineDown(const int line)
{
    for (int i = 0; i<py; i++)
    {
        Box[line*2-1][i] = Box[line*2-3][i];
    }
}

void dialogBox::AddQuote(const char * quote)
{
    for (int j = NumberOfLines; j>1; --j)
    {
        lineDown(j);
    }

    for (int i = 11, j = 0; i<strlen(quote)+11; i++,j++)
    {
        Box[1][i+1] = quote[j];
    }
    
    for (int i = unsigned(strlen(quote))+12; i<py; i++)
    {
        Box[1][i] = ' ';
    }
    Box[1][1] = '[';
    Box[1][2] = (char)((int)'0')+GMGameMenu::GlobalTime.getDay()/10;
    Box[1][3] = (char)((int)'0')+GMGameMenu::GlobalTime.getDay()%10;
    Box[1][4] = '/';
    Box[1][5] = (char)((int)'0')+GMGameMenu::GlobalTime.getHour()/10;
    Box[1][6] = (char)((int)'0')+GMGameMenu::GlobalTime.getHour()%10;
    Box[1][7] = '/';
    Box[1][8] = (char)((int)'0')+GMGameMenu::GlobalTime.getMin()/10;
    Box[1][9] = (char)((int)'0')+GMGameMenu::GlobalTime.getMin()%10;
    Box[1][10] = ']';
}

void dialogBox::clearBox()
{
    {
        for(int j = 1; j<px; j++)
        {
            for (int i = 1; i<py; i++)
            {
                    Box[j][i] = ' ';
            }
        }
    }
}

int dialogBox::getPy() const
{
    return py;
}
int dialogBox::getPx() const
{
    return px;
}
char** dialogBox::getBox() const
{
    return Box;
}