#pragma once

enum DayTime
{
    Day,
    Night,
    Dawn
};

class ptime
{
float accumulator;
int pSec;
int pMin;
int pHour;
int pDay;
DayTime DTime;

public:
ptime(int,int,int);
void fly(float fElapsedTime);
void load(const int day, const int hour, const int minute);
void checkDTime();
const int getSec();
const int getMin();
const int getHour();
const int getDay();
const int getDTime();
};

