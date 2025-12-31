#pragma once
#include "item.h"

class equipment : public item
{
protected:
public:
    equipment(const int Price, const int restriction);
    int getRestriction() const;
};