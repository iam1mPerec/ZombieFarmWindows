#include <iostream>
#include "Party.h"
#include "titles.h"

using namespace std;

party::party():
Head(nullptr),
count(8)
{
    Head = new unit();
    unit* aloc = Head;
    for (int i = 1; i<count; i++)
    {
        unit* New = new unit();
        aloc->setNext(New);
        aloc = aloc->getNext();
    }
}

bool party::allHealed()
{
    for (int i = 0; i < 8 ; i++)
    {
        unit* Unit = getUnit(i);
        
        if(Unit->IsDamaged())
        {
            return false;
        }
        else
        {
            continue;
        }
    }
    return true;
}

void party::allFine()
{
    for (int i = 0; i < 8 ; i++)
    {
        unit* Unit = getUnit(i);
        
        if(!Unit->IsAlive())
        {
            continue;
        }
        else
        {
            Unit->fine();
        }
    }
}

void party::blincker()
{
    for (int i = 0; i<8; i++)
    {
        unit* Unit = getUnit(i);
        
        if(!Unit->IsAlive())
        {
            continue;
        }
        else
        {
            int count = Unit->getBlinck();
            if (count)
            {
                count--;
                Unit->fine();
            }
            else
            {
                count = rand()%12+4;
                Unit->blincking();
            }
            Unit->setBlinck(count);
        }
    }
}

void party::massRevive()
{
    unit* aloc = Head;
    for (int i = 0; i<count; i++)
    {
        aloc->revive();
        aloc = aloc->getNext();
    }
}

unit* party::getAttacker() const
{
    if (getAttackerPos() != -1)
    {
        return getUnit(getAttackerPos());
    }
    
    return nullptr;
}

int party::getHighestPriority() const
{
    int highest = 0;
    unit* aloc = Head;
    
    for (int i = 0; i<count; i++)
    {
        if(aloc->getPriority() > highest && aloc->getTurn())
        {
            highest = aloc->getPriority();
        }
        aloc = aloc->getNext();
    }
    
    return highest;
}

int party::getAttackerPos() const
{
    if (getHighestPriority() != 0)
    {
        unit* aloc = Head;
    
        for (int i = 0; i<count; i++)
        {
            if(aloc->getPriority() == getHighestPriority() && aloc->getTurn())
            {
                aloc->resetShild();
                return i;
            }
            aloc = aloc->getNext();
        }
    }
    return -1;
}

int party::rollcall() const
{
    int size = 0;
    unit* aloc = Head;
    for (int i = 0; i<count; i++)
    {
        if (aloc->getType() != title::untitled && aloc->IsAlive())
        {
            size++;
        }
        aloc = aloc->getNext();
    }
    return size;
}

void party::addSolder()
{
    if (rollcall()<count)
    {
    unit* aloc = Head;
    unit* next = nullptr;
        if (aloc->getType() == title::untitled)
        {
            next = aloc->getNext();
            delete aloc;
            aloc = new class solder();
            aloc->setNext(next);
            Head = aloc;
        }
        else
        {
            unit* temp = nullptr;
            for (int i = 0; i<count; i++)
            {
                if (aloc->getNext()->getType() == title::untitled)
                {
                    temp = aloc->getNext();
                    next = temp->getNext();
                    delete temp;
                    temp = new class solder();
                    aloc->setNext(temp);
                    temp->setNext(next);
                    i = count;
                }
                else
                {
                    aloc = aloc->getNext();
                }
            }
        }
    }
}

void party::addSolder(const int J, const int I, const int LVL, const int HP)
{
    int position = J*4+I;
    if (position<0)
    {
        position = 0;
    }
    if (position>count)
    {
        position = count;
    }
    unit* aloc = Head;
    unit* next = nullptr;
    if (position == 0)
    {
        next = aloc->getNext();
        delete aloc;
        aloc = new class solder(LVL, HP);
        aloc->setNext(next);
        Head = aloc;
    }
    else
    {
        for (int i = 1; i<position; i++)
        {
            aloc = aloc->getNext();
        }
        unit* temp = aloc->getNext();
        next = temp->getNext();
        delete temp;
        temp = new class solder(LVL,HP);
        aloc->setNext(temp);
        temp->setNext(next);
    }
}

void party::addSolder(const int J, const int I, const int LVL)
{
    addSolder(J, I, LVL, 9999);
}
void party::addTank  (const int J, const int I, const int LVL)
{
    addTank(J, I, LVL, 9999);
}
void party::addSniper(const int J, const int I, const int LVL)
{
    addSniper(J, I, LVL, 9999);
}
void party::addHealer(const int J, const int I, const int LVL)
{
    addHealer(J, I, LVL, 9999);
}

void party::addSolder(const int J, const int I)
{
    addSolder(J, I, 1, 99999);
}

void party::addSniper(const int J, const int I)
{
    addSniper(J, I, 1, 99999);
}

void party::addHealer(const int J, const int I)
{
    addHealer(J, I, 1, 99999);
}

void party::addTank(const int J, const int I)
{
    addTank(J, I, 1, 99999);
}

void party::addTank(const int J, const int I, const int LVL, const int HP)
{
    int position = J*4+I;
    if (position<0)
    {
        position = 0;
    }
    if (position>count)
    {
        position = count;
    }
    unit* aloc = Head;
    unit* next = nullptr;
    if (position == 0)
    {
        next = aloc->getNext();
        weapon * W = aloc->getWeapon();
        helmet * H = aloc->getHelmet();
        chest  * C = aloc->getChest();
        gloves * G = aloc->getGloves();
        boots  * B = aloc->getBoots();
        delete aloc;
        aloc = new class tank(LVL,HP);
        aloc->equipWeapon(W);
        aloc->equipHelmet(H);
        aloc->equipChest (C);
        aloc->equipGloves(G);
        aloc->equipBoots (B);
        aloc->setNext(next);
        Head = aloc;
    }
    else
    {
        for (int i = 1; i<position; i++)
        {
            aloc = aloc->getNext();
        }
        unit* temp = aloc->getNext();
        next = temp->getNext();
        weapon * W = temp->getWeapon();
        helmet * H = temp->getHelmet();
        chest  * C = temp->getChest();
        gloves * G = temp->getGloves();
        boots  * B = temp->getBoots();
        delete temp;
        temp = new class tank(LVL,HP);
        temp->equipWeapon(W);
        temp->equipHelmet(H);
        temp->equipChest (C);
        temp->equipGloves(G);
        temp->equipBoots (B);
        aloc->setNext(temp);
        temp->setNext(next);
    }
}

void party::addSniper(const int J, const int I, const int LVL, const int HP)
{
    int position = J*4+I;
    if (position<0)
    {
        position = 0;
    }
    if (position>count)
    {
        position = count;
    }
    unit* aloc = Head;
    unit* next = nullptr;
    if (position == 0)
    {
        next = aloc->getNext();
        weapon * W = aloc->getWeapon();
        helmet * H = aloc->getHelmet();
        chest  * C = aloc->getChest();
        gloves * G = aloc->getGloves();
        boots  * B = aloc->getBoots();
        delete aloc;
        aloc = new class sniper(LVL, HP);
        aloc->equipWeapon(W);
        aloc->equipHelmet(H);
        aloc->equipChest (C);
        aloc->equipGloves(G);
        aloc->equipBoots (B);
        aloc->setNext(next);
        Head = aloc;
    }
    else
    {
        for (int i = 1; i<position; i++)
        {
            aloc = aloc->getNext();
        }
        unit* temp = aloc->getNext();
        next = temp->getNext();
        weapon * W = temp->getWeapon();
        helmet * H = temp->getHelmet();
        chest  * C = temp->getChest();
        gloves * G = temp->getGloves();
        boots  * B = temp->getBoots();
        delete temp;
        temp = new class sniper(LVL, HP);
        temp->equipWeapon(W);
        temp->equipHelmet(H);
        temp->equipChest (C);
        temp->equipGloves(G);
        temp->equipBoots (B);
        aloc->setNext(temp);
        temp->setNext(next);
    }
}

void party::addHealer(const int J, const int I, const int LVL, const int HP)
{
    int position = J*4+I;
    if (position<0)
    {
        position = 0;
    }
    if (position>count)
    {
        position = count;
    }
    unit* aloc = Head;
    unit* next = nullptr;
    if (position == 0)
    {
        next = aloc->getNext();
        weapon * W = aloc->getWeapon();
        helmet * H = aloc->getHelmet();
        chest  * C = aloc->getChest();
        gloves * G = aloc->getGloves();
        boots  * B = aloc->getBoots();
        delete aloc;
        aloc = new class healer(LVL, HP);
        aloc->equipWeapon(W);
        aloc->equipHelmet(H);
        aloc->equipChest (C);
        aloc->equipGloves(G);
        aloc->equipBoots (B);
        aloc->setNext(next);
        Head = aloc;
    }
    else
    {
        for (int i = 1; i<position; i++)
        {
            aloc = aloc->getNext();
        }
        unit* temp = aloc->getNext();
        next = temp->getNext();
        weapon * W = temp->getWeapon();
        helmet * H = temp->getHelmet();
        chest  * C = temp->getChest();
        gloves * G = temp->getGloves();
        boots  * B = temp->getBoots();
        delete temp;
        temp = new class healer(LVL, HP);
        temp->equipWeapon(W);
        temp->equipHelmet(H);
        temp->equipChest (C);
        temp->equipGloves(G);
        temp->equipBoots (B);
        aloc->setNext(temp);
        temp->setNext(next);
    }
}

int party::getCount() const
{
    return count;
}

void party::swap(const int y1, const int x1, const int y2, const int x2)
{
    int position_1 = y1*4+x1;
    int position_2 = y2*4+x2;
    unit* aloc_1 = Head;
    unit* aloc_2 = Head;
    unit* next_1 = nullptr;
    unit* next_2 = nullptr;
    if (position_1 != position_2)
    {
        if (position_2 < position_1)
        {
            int swap = position_2;
            position_2 = position_1;
            position_1 = swap;
        }
        
        if (position_1 == 0)
        {
            if (position_2 == 1)
            {
                aloc_2 = aloc_2->getNext();
                next_2 = aloc_2->getNext();
                aloc_1->setNext(next_2);
                aloc_2->setNext(Head);
                Head = aloc_2;
            }
            else
            {
                for (int i = 1; i<position_2; i++)
                {
                    aloc_2 = aloc_2->getNext();
                }
                next_1 = aloc_1->getNext();
                next_2 = aloc_2->getNext();
                aloc_1->setNext(next_2->getNext());
                next_2->setNext(next_1);
                aloc_2->setNext(aloc_1);
                Head = next_2;
            }
        }
        else
        {
            if (position_2 - position_1 == 1)
            {
                unit* prev = Head;
                for (int i = 1; i<position_1; i++)
                {
                     prev = prev->getNext();
                }
                aloc_1 = prev->getNext();
                
                for (int i = 0; i<position_2; i++)
                {
                    aloc_2 = aloc_2->getNext();
                }
                
                aloc_1->setNext(aloc_2->getNext());
                aloc_2->setNext(aloc_1);
                prev->setNext(aloc_2);
            }
            else
            {
                unit* prev_1 = Head;
                unit* prev_2 = Head;
                unit* next_2;
                for (int i = 1; i<position_1; i++)
                {
                    prev_1 = prev_1->getNext();
                }
                
                for (int i = 1; i<position_2; i++)
                {
                    prev_2 = prev_2->getNext();
                }
                aloc_1 = prev_1->getNext();
                aloc_2 = prev_2->getNext();
                next_2 = aloc_2->getNext();
                prev_1->setNext(aloc_2);
                prev_2->setNext(aloc_1);
                aloc_2->setNext(aloc_1->getNext());
                aloc_1->setNext(next_2);
            }
        }
    }
}

void party::resetTurns()
{
    unit * aloc = Head;
    for (int i = 0; i<count; i++)
    {
        aloc->resetTurns();
        aloc = aloc->getNext();
    }
}

void party::drawAll()
{
    unit * aloc = Head;
    
    for (int i = 0; i<count; i++)
    {
        aloc->draw();
        aloc = aloc->getNext();
    }
}

unit* party::getUnit(const int Position) const
{
    int position = Position;
    
    unit* aloc = Head;
    
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

unit* party::getUnit(const int J, const int I) const
{
    int position = J*4 + I;
    return getUnit(position);
}