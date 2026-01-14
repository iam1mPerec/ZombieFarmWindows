#include <iostream>
#include "event.h"
#include "str.h"

using namespace std;

event::event():
    pDay(0),
    pHour(0),
    pMin(0),
    priority(0),
    done(false),
    plant(false),
    Next(nullptr),
	name(nullptr)
{}

char * event::getHeader()
{
    return header;
}

void event::update(int tick)
{
    if (done) return;
	pMin -= tick;
    if (pMin < 0)
    {
        pMin = 59;
        pHour -= 1;

        if (pHour < 0)
        {
            pHour = 23;
            pMin = 59;
            pDay -= 1;

            if (pDay < 0)
            {
                pDay = 0;
                pHour = 0;
                pMin = 0;
                triger();
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
    return false;
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
