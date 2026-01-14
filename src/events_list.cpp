#include <iostream>
#include "events_list.h"
#include "str.h"

using namespace std;

events_list::events_list():
Head(nullptr),
Tail(nullptr),
count(0)
{
}

void events_list::AddPlant(field &MField, char **M,const int Size, dialogBox &Box, enum plants plant_type, int pday, int phour, int pmin)
{
    int priority = pday*24*60+phour*60+pmin;
    
    event * aloc = Head;
    if(count==0)
    {
        Head = new plant(MField, M,Size, Box, plant_type, pday, phour, pmin);
        Tail = Head;
    }
    else if(Head->getPriority() > priority)
    {
        aloc = new plant(MField, M,Size, Box, plant_type, pday, phour, pmin);
        aloc->setNext(Head);
        Head = aloc;
    }
    else
    {
        for (int i = 0; i<count-1; i++)
        {
            if (priority < aloc->getNext()->getPriority())
            {
                i=count;
            }
            else
            {
                aloc = aloc->getNext();
            }
        }
        event * ptr = new plant(MField, M,Size, Box, plant_type, pday, phour, pmin);
        ptr->setNext(aloc->getNext());
        aloc->setNext(ptr);
        if (ptr->getNext() == nullptr)
        {
            Tail = ptr;
        }
    }
    count++;
}

void events_list::AddPlant(field &MField,char** M,const int Size, dialogBox &Box, enum plants plant_type)
{
    int pday = 0;
    int phour = 0;
    int pmin = 0;
    
    switch (plant_type)
    {
        case potato:
            pday  = 0;
            phour = 1;
            pmin  = 0;
            break;
            
        case corn:
            pday  = 0;
            phour = 1;
            pmin  = 30;
            break;
            
        case tomato:
            pday  = 0;
            phour = 4;
            pmin  = 0;
            break;
        case carrot:
            pday  = 0;
            phour = 7;
            pmin  = 0;
            break;
            
        case pumpkin:
            pday  = 0;
            phour = 7;
            pmin  = 35;
            break;
            
        case cherry:
            pday  = 0;
            phour = 15;
            pmin  = 0;
            break;
            
        default:
            pday  = 0;
            phour = 0;
            pmin  = 0;
            break;
    }
    AddPlant(MField, M,Size, Box, plant_type, pday, phour, pmin);
    }

void events_list::AddBuilding(field &MField, farmer *f, dialogBox &Box, structures building_type, constructions &possession,
                              char** ar, int pday, int phour, int pmin)
{
    int priority = pday*24*60+phour*60+pmin;
    
    event * aloc = Head;
    
    if(count==0)
    {
        Head = new building(MField, f, Box, building_type, possession, ar, pday, phour, pmin);
        Tail = Head;
    }
    
    else if(Head->getPriority() > priority)
    {
        aloc = new building(MField, f, Box, building_type, possession, ar, pday, phour, pmin);
        aloc->setNext(Head);
        Head = aloc;
    }
    else
    {
        for (int i = 0; i<count-1; i++)
        {
            if (priority < aloc->getNext()->getPriority())
            {
                i=count;
            }
            else
            {
                aloc = aloc->getNext();
            }
        }
        event * ptr = new building(MField, f, Box, building_type, possession, ar, pday, phour, pmin);
        ptr->setNext(aloc->getNext());
        aloc->setNext(ptr);
        if (ptr->getNext() == nullptr)
        {
            Tail = ptr;
        }
    }
    count++;
}

void events_list::AddBuilding(field &MField, farmer * f, dialogBox &Box,
                              structures building_type, constructions &possession, char** ar)
{
    int pday  = 0;
    int phour = 0;
    int pmin  = 0;
    
    switch (building_type)
    {
        case fence:
        {
            switch (MField.getSize())
            {
                case Small:
                    pday  = 0;
                    phour = 2;
                    pmin  = 30;
                    break;
                    
                case Medium:
                    pday  = 0;
                    phour = 5;
                    pmin  = 0;
                    break;
                    
                case Large:
                    pday  = 0;
                    phour = 10;
                    pmin  = 25;
                    break;
                    
                default:
                    break;
            }
            break;
            
        case tent:
            {
                switch (possession.getTentSize())
                {
                    case noTent:
                        pday  = 0;
                        phour = 2;
                        pmin  = 45;
                        break;
                        
                    case TentS:
                        pday  = 0;
                        phour = 5;
                        pmin  = 50;
                        break;
                        
                    case TentM:
                        pday  = 0;
                        phour = 7;
                        pmin  = 40;
                        break;
                        
                    default:
                        break;
                }
                break;
        }
        case tunel:
            pday  = 0;
            phour = 5;
            pmin  = 0;
            break;
        
        case barracks:
            pday  = 0;
            phour = 10;
            pmin  = 0;
            break;
            
        case house:
        {
            switch (possession.getHouseSize())
            {
                case simple:
                    pday  = 0;
                    phour = 5;
                    pmin  = 0;
                    break;
                    
                case roomy:
                    pday  = 0;
                    phour = 45;
                    pmin  = 0;
                    break;
                default:
                    break;
            }
        }
            break;
        default:
            break;
    }
}
    AddBuilding(MField, f, Box, building_type, possession, ar, pday, phour, pmin);
    }

bool events_list::check4(const char* Name) const
{
    bool present = false;
    event* aloc = Head;
    for (int i = 0; i<count; i++)
    {
        if (equals(aloc->getName(), Name))
        {
            i = count;
            present = true;
        }
        aloc = aloc->getNext();
    }
    
    return present;
}

void events_list::AddWork(farmer * f, dialogBox &Box, enum jobs type, resources &Res, int pday, int phour, int pmin)
{
    int priority = pday*24*60+phour*60+pmin;
    
    event * aloc = Head;
    
    if(count==0)
    {
        Head = new work(f, Box, type, Res);
        Tail = Head;
    }
    
    else if(Head->getPriority() > priority)
    {
        aloc = new work(f, Box, type, Res);
        aloc->setNext(Head);
        Head = aloc;
    }
    else
    {
        for (int i = 0; i<count-1; i++)
        {
            if (priority < aloc->getNext()->getPriority())
            {
                i=count;
            }
            else
            {
                aloc = aloc->getNext();
            }
        }
        event * ptr = new work(f, Box, type, Res);
        ptr->setNext(aloc->getNext());
        aloc->setNext(ptr);
        if (ptr->getNext() == nullptr)
        {
            Tail = ptr;
        }
    }
    count++;
}

void events_list::AddWork(farmer * f, dialogBox &Box, enum jobs type, resources &Res)
{
    int pday  = 0;
    int phour = 0;
    int pmin  = 0;
    
    switch (type)
    {
        case jobs::chop:
            pday  = 0;
            phour = 5;
            pmin  = 0;
            break;
            
        case jobs::adventure:
            pday  = 0;
            phour = 5;
            pmin  = 0;
            break;
            
        default:
            pday  = 0;
            phour = 0;
            pmin  = 0;
            break;
    }
    AddWork(f, Box, type, Res, pday, phour, pmin);
    }

void events_list::check4Dead()
{
        if (getCount()>0)
        {
            event* aloc = Head;
            
            for (int i = 0; i<count; i++)
            {
                if (!aloc->getDay() && !aloc->getHour() && !aloc->getMin() && !aloc->show_progress())
                {
                    deleteNode(aloc);
                }
                 aloc = aloc->getNext();
            }
        }
}

void events_list::deleteNode(event* name)
{
    //проверка не пустой ли список
    if (count)
    {
       event* aloc = Head;
        
        if (Head == name)
        {
            aloc = aloc->getNext();
            Head->Del();
            Head = aloc;
            count--;
        }
        else
        {
            for (int i = 0; i<count; i++)
            {
                if (aloc->getNext() == name)
                {
                    aloc->setNext(name->getNext());
                    name->Del();
                    i=count;
                }
                else
                {
                    aloc = aloc->getNext();
                }
            }
            count--;
        }
    }
}

event * events_list::getHead()
{
    return Head;
}

int events_list::getCount()
{
    return count;
}

event * events_list::listing(const int l)
{
    if(l>count)
    {
        return nullptr;
    }
    event * aloc = Head;
    for (int i = 0; i<l; i++)
    {
        aloc = aloc->getNext();
    }
    return aloc;
}