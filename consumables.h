#pragma once
#include "item.h"

enum consume
{
    potion,
    kit,
    grenade,
    bomb,
    revive,
    bandages
};

class consumables : public item
{
protected:
    const enum consume consumable;
    int count;
    const int MaxCount;
    
public:
    consumables(const enum consume type, const int Count, const int Price);
    consumables(const enum consume type, const int Count, const int MaxCount, const int Price);
    int getCount() const;
    int getMaxCount() const;
    int addCount(const int Count);
    void setCount(const int n);
    void consume();
    void blank();
};