#pragma once
#include "Unit.h"
#include "Tank.h"
#include "Sniper.h"
#include "Healer.h"

class UpGrade
{
    unit * Head;
    const int count;
public:
    UpGrade();
    unit* operator[](const int i);
};