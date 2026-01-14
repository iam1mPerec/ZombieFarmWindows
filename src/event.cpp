#include <iostream>
#include "event.h"
#include "str.h"

using namespace std;

event::event()
{
}

char * event::getHeader()
{
    return header;
}

void event::in_progress(float fElapsedTime)
{
    if(!done)
    {
        pSec -= 60 * fElapsedTime;
        
        if(pSec <= 0)
        {
            pSec  = 60;
            pMin -= 1;
            
                if (pMin < 0)
                {
                    pMin   = 59;
                    pSec   = 60;
                    pHour -= 1;
                    
                    if(pHour < 0)
                    {
                        pHour = 23;
                        pMin  = 59;
                        pSec  = 60;
                        pDay -= 1;
                        
                        if(pDay < 0)
                        {
                            pDay  = 0;
                            pHour = 0;
                            pMin  = 0;
                            pSec  = 0;
                            triger();
                        }
                    }
                }
            }
        }
}

void event::Del()
{
    
}

int event::getPriority()
{
    priority = pDay*24*60+pHour*60+pMin;
    return priority;
}

int event::getDay() const
{
    return pDay;
}
int event::getHour() const
{
    return pHour;
}
int event::getMin() const
{
    return pMin;
}
int event::getSec() const
{
    return pSec;
}
void event::setNext(event* new_event)
{
   Next = new_event;
}
event * event::getNext()
{
    return Next;
}
char* event::getName()
{
    return name;
}

int event::getOption() const
{
    return 0;
}

char ** event::getMatrix()
{
    return nullptr;
}

bool event::show_progress() const
{
    return 0;
}
int event::getAmmount()
{
    return 0;
}
int event::getCost()
{
    return 0;
}
int event::getReward()
{
    return 0;
}
void event::triger()
{
    
}