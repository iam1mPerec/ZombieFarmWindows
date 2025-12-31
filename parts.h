#pragma once
#include "item.h"
#include "ItemTypes.h"

class parts : public item
{
    const Parts part;
    parts(const Parts type, const int Price);
public:
    int getPartType() const;
};