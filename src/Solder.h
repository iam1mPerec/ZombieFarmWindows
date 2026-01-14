#pragma once
#include "Unit.h"

class solder: public unit
{
public:
    solder();
    solder(const int LVL, const int HP);
    void stat();
    void create();
    void picture();
};