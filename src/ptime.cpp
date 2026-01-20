#include "ptime.h"

ptime::ptime(int pD, int pH, int pM):
    accumulator(0.0f),
    pSec(0),
    pMin(pM),
    pHour(pH),
    pDay(pD)
{
    if(pM>60||pM<0)
    {
        pMin = 30;
    }
    if(pH>24||pH<0)
    {
        pHour = 8;
    }
    if(pD>99||pD<1)
    {
        pDay = 1;
    }
    
    checkDTime();
}

const int ptime::getMin()
{
    return pMin;
}
const int ptime::getHour()
{
    return pHour;
}
const int ptime::getDay()
{
    return pDay;
}
const int ptime::getDTime()
{
    return DTime;
}
const int ptime::getSec()
{
    return pSec;
}

void ptime::load(const int day, const int hour, const int minute)
{
    pDay  = day;
    pHour = hour;
    pMin  = minute;
    
    checkDTime();
}

void ptime::checkDTime()
{
    if(pHour >= 5 && pHour < 8)
    {
        DTime = DayTime::Dawn;
    }
    
    else if(pHour >= 8 && pHour < 23)
    {
        DTime = DayTime::Day;
    }
    
    else
    {
        DTime = DayTime::Night;
    }
}
void ptime::fly(float fElapsedTime)
{
	accumulator += fElapsedTime;
    if(accumulator >= 0.1f)
    {
		pSec +=6;
        accumulator -= 0.1f;
	}
    if (pSec >= 60)
    {
        pSec = 0;
        pMin += 1;

        if (pMin >= 60)
        {
            pMin = 0;
            pHour += 1;

            checkDTime();

            if (pHour >= 24)
            {
                pHour = 0;
                pDay += 1;
            }
        }
    }
}