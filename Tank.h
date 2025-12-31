#pragma once
#include "Unit.h"

class tank: public unit
{
public:
    tank();
    tank(const int LVL, const int HP);
    void stat();
    void create();
    void picture();
};