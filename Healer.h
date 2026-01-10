#pragma once
#include "Unit.h"

class healer: public unit
{
public:
    healer();
    healer(const int LVL, const int HP);
    void stat();
    void create();
};