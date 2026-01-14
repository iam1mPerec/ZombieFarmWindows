#pragma once
#include "item.h"

class inventory
{
    item* Head;
    item* Tail;
    int count;
    
public:
    inventory();
    item* getItem(const int position);
    void  addItem(item* aloc);
    int   getCount() const;
    int   getNumberOfPages() const;
    void  removeItem(const int Count);
    void  replaceItem(item* ITEM, const int Count);
    void  Check4Dead();
};