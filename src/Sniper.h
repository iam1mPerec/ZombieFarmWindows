#pragma once
#include "Unit.h"

class sniper: public unit
{
public:
    sniper();
    sniper(const int LVL, const int HP);
    void stat();
    void create();
    void picture();
};