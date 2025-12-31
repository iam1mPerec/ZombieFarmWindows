#include <iostream>
#include "consumables.h"
#include "str.h"

using namespace std;

consumables::consumables(const enum consume type, const int Count, const int maxCount, const int Price):
item(itemType::consumables, Price, 0),
consumable(type),
count(Count),
MaxCount(maxCount)
{
    if(count)
    {
        if(count > MaxCount)
        {
            count = MaxCount;
        }
        blank();
        showCount();
    }
}

consumables::consumables(const enum consume type, const int Count, const int Price):
item(itemType::consumables, Price, 0),
consumable(type),
count(Count),
MaxCount(99)
{
    if(count)
    {
        if(count > MaxCount)
        {
            count = MaxCount;
        }
        blank();
        showCount();
    }
}

int consumables::getCount() const
{
    if (count)
    {
        return count;
    }
    else
    {
        return -1;
    }
}

int consumables::getMaxCount() const
{
    return MaxCount;
}

void consumables::consume()
{
    if (count)
    {
        count--;
        showCount();
    }
}

void consumables::setCount(const int n)
{
    count = n;
    blank();
    showCount();
}

int consumables::addCount(const int Count)
{
    count += Count;
    
    if(count > 0)
    {
        if(count > MaxCount)
        {
            int overall = count;
            count = MaxCount;
            blank();
            showCount();
            return overall - MaxCount;
        }
        else
        {
            blank();
            showCount();
            return 0;
        }
    }
    else
    {
        count = -1;
        return  -1;
    }
}

void consumables::blank()
{
    if (MaxCount)
    {
        for (int i = LenOfNumbers(MaxCount); i>0; i--)
        {
            pic[2][11-i] = ' ';
        }
    }
}