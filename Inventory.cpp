#include <iostream>
#include "str.h"
#include "Inventory.h"

using namespace std;

inventory::inventory():
Head(nullptr),
Tail(nullptr),
count(0)
{
    
}

item* inventory::getItem(const int Position)
{
    item* aloc = Head;
    
    int position = Position;
    
    if (position < 0)
    {
        position = 0;
    }
    if (position > count)
    {
        position = count;
    }
    
    for (int i = 0; i<position; i++)
    {
        aloc = aloc->getNext();
    }
    
    return aloc;
}

void inventory::addItem(item *Item)
{
    if(!Item->getCount())
    {
        if (!count)
        {
            Head = Item;
            Tail = Head;
        }
        else
        {
            Tail->setNext(Item);
            Tail = Tail->getNext();
        }
        count++;
    }
    else
    {
        item* aloc  = Head;
        int COUNT   = 0;
        int remains = Item->getCount();
        
        char alocName[20];
        char itemName[20];
        
        for(int i = 0; i < 20; i++)
        {
            itemName[i] = Item->getName(i);
        }
        
        while (COUNT < count)
        {
            for(int i = 0; i < 20; i++)
            {
                alocName[i] = aloc->getName(i);
            }
            
            if(equals(itemName, alocName))
            {
                remains = aloc->addCount(remains);
                
                if(remains)
                {
                    Item->setCount(remains);
                }
                else
                {
                    delete Item;
                    break;
                }
            }
            aloc = aloc->getNext();
            COUNT++;
        }
        
        if(remains)
        {
            if (!count)
            {
                Head = Item;
                Tail = Head;
            }
            else
            {
                Tail->setNext(Item);
                Tail = Tail->getNext();
            }
            count++;
        }
    }
}

int inventory::getNumberOfPages() const
{
    bool remainder = count%18;
    int pages = (count/18 + remainder)-1;
    
    if (pages == -1)
    {
        pages = 0;
    }
    return pages;
}

void inventory::Check4Dead()
{
    item * aloc = Head;
    
    for (int i = 0; i < count; i++)
    {
        if(aloc->getCount() == -1)
        {
            removeItem(i);
            Check4Dead();
            break;
        }
        else
        {
            aloc = aloc->getNext();
        }
    }
}

void inventory::removeItem(const int COUNT)
{
    item* aloc = Head;
    
    if (!COUNT)
    {
        Head = Head->getNext();
        
        if(aloc->getType() == itemType::consumables)
        {
            delete aloc;
        }
    }
    else if(COUNT > 0 && COUNT < count)
    {
        for (int i = 0; i<COUNT-1; i++)
        {
            aloc = aloc->getNext();
        }
        item* remove = aloc->getNext();
        aloc->setNext(remove->getNext());
        
        if(aloc->getType() == itemType::consumables)
        {
            delete remove;
        }
        
        if (count == COUNT+1)
        {
            Tail = aloc;
        }
    }
    else
    {
        
    }
    count--;
}

void inventory::replaceItem(item *ITEM, const int COUNT)
{
    if (ITEM != nullptr)
    {
        item* aloc = Head;
        if (!COUNT)
        {
            ITEM->setNext(aloc->getNext());
            Head = ITEM;
        }
        else if(COUNT>0 && COUNT <= count)
        {
            for (int i = 0; i<COUNT-1; i++)
            {
                aloc = aloc->getNext();
            }
            item* remove = aloc->getNext();
            aloc->setNext(ITEM);
            ITEM->setNext(remove->getNext());
            
            if (count == COUNT)
            {
                Tail = ITEM;
            }
        }
    }
    else
    {
        removeItem(COUNT);
    }
}

int inventory::getCount() const
{
    return count;
}