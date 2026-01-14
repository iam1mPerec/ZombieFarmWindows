#include <iostream>
#include "ProgressMenu.h"
#include "events_list.h"
#include "screen.h"

using namespace std;

ProgressMenu::ProgressMenu(char ** screen, events_list &list):
menu(nullptr),
mx(BottomPlank - 5),
my(y - SidePlank-3),
events(list),
screen(screen)
{
    menu = new char * [mx];
    for (int i = 0; i<mx; i++)
    {
        menu[i] = new char [my];
    }
}

void ProgressMenu::clear()
{
    for (int j = 0; j<mx; j++)
    {
        for (int i = 0; i<my; i++)
        {
            menu[j][i] = ' ';
        }
    }
}

void ProgressMenu::showProgress(float fElapsedTime)
{
    clear();
    events.check4Dead();
    int count = events.getCount();
    
	//count the amount of events to show
    
    if (count > BottomPlank/2 - 1)
    {
        count = BottomPlank/2 - 1;
    }
    for (int j = 0; j<count; j++)
    {
        for (int i = 0; i<y - SidePlank-3; i++)
        {
            menu[j*2][i] = events.listing(j)->getHeader()[i];
        }
    }
    for (int j = 0; j<mx; j++)
    {
        for (int i = 0; i<my; i++)
        {
            screen[j+5][i+SidePlank+2] = menu[j][i];
        }
    }
    showTimer(fElapsedTime);
}

void ProgressMenu::showTimer(float fElapsedTime)
{
    if (events.getCount()>0)
    {
        event* aloc = events.getHead();
        
        for (int i = 0; i<events.getCount(); i++)
        {
            if (aloc->getDay() || aloc->getHour() || aloc->getMin())
            {
                screen[i*2+5][y-10] = (char)((int)'0')+aloc->getDay()/10;
                screen[i*2+5][y-9]  = (char)((int)'0')+aloc->getDay()%10;
                screen[i*2+5][y-8]  = ':';
                screen[i*2+5][y-7]  = (char)((int)'0')+aloc->getHour()/10;
                screen[i*2+5][y-6]  = (char)((int)'0')+aloc->getHour()%10;
                screen[i*2+5][y-5]  = ':';
                screen[i*2+5][y-4]  = (char)((int)'0')+aloc->getMin()/10;
                screen[i*2+5][y-3]  = (char)((int)'0')+aloc->getMin()%10;
            }
            
            else
            {
                screen[i*2+5][y-6] = 'd';
                screen[i*2+5][y-5] = 'o';
                screen[i*2+5][y-4] = 'n';
                screen[i*2+5][y-3] = 'e';
            }
            aloc->in_progress(fElapsedTime);
            aloc = aloc->getNext();
        }
    }
}

char** ProgressMenu::getMenu() const
{
    return menu;
}

int ProgressMenu::get_mx() const
{
    return mx;
}

int ProgressMenu::get_my() const
{
    return my;
}

ProgressMenu::~ProgressMenu()
{
    for (int i = 0; i<mx; i++)
    {
        delete [] menu[i];
    }
    delete [] menu;
}