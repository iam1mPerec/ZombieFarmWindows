#include <iostream>
#include "Horde.h"
#include "time.h"

using namespace std;

Horde::Horde():
Head(nullptr),
Tail(nullptr),
count(0),
wave(0),
RewardExp(0),
RewardMoney(0),
NumberOfWaves(0)
{
}

void Horde::setWave(const int i)
{
    wave = i;
}

int Horde::getMoney() const
{
    return RewardMoney;
}

int Horde::getExp() const
{
    return RewardExp;
}

void Horde::setExp(const int ammount)
{
    RewardExp = ammount;
}

void Horde::setMoney()
{
   RewardMoney = 0;
}

void Horde::setExp()
{
    RewardExp = 0;
}

void Horde::setMoney(const int ammount)
{
    RewardMoney = ammount;
}

int Horde::getHighestPriority() const
{
    int highest = 0;
    zombie* aloc = Head;
    
    int c = count;
    if (c>8)
    {
        c = 8;
    }
    
    for (int i = 0; i<c; i++)
    {
        if(aloc->getPriority() > highest && aloc->getTurn() && aloc->getType() != wasted)
        {
            highest = aloc->getPriority();
        }
        aloc = aloc->getNext();
    }
    
    return highest;
}

void Horde::deleteAll()
{
    zombie * aloc = Head;
    int enemies = count;
    
    for (int i = 0; i<enemies; i++)
    {
        aloc = aloc->getNext();
        delete [] Head;
        Head = aloc;
        count--;
    }
    wave = 0;
}

void Horde::deleteWave()
{
    zombie * aloc = Head;
    int enemies = count;
    if (enemies > 8)
    {
        enemies = 8;
        wave++;
    }
    else
    {
        wave = 0;
    }
    for (int i = 0; i<enemies; i++)
    {
        aloc = aloc->getNext();
        delete [] Head;
        Head = aloc;
        count--;
    }
}

zombie* Horde::getAttacker() const
{
    if (getAttackerPos() != -1)
    {
        return getUnit(getAttackerPos());
    }

    return nullptr;
}

int Horde::getAttackerPos() const
{
    if (getHighestPriority() != 0)
    {
        zombie* aloc = Head;
        
        int c = count;
        
        if (c>8)
        {
            c = 8;
        }
        
        for (int i = 0; i<c; i++)
        {
            if(aloc->getPriority() == getHighestPriority() && aloc->getTurn())
            {
                return i;
            }
            aloc = aloc->getNext();
        }
    }
    return -1;
}

int Horde::getNumberOfWaves() const
{
    return NumberOfWaves;
}

int Horde::getWave() const
{
    return wave;
}

void Horde::resetWaves()
{
    wave = 0;
}

void Horde::resetTurns()
{
    zombie * aloc = Head;
    for (int i = 0; i<count; i++)
    {
        aloc->resetTurns();
        aloc = aloc->getNext();
    }
}

bool Horde::exists(const int position) const
{
    if ((position >= 0) && (position < 8) && (position < count))
    {
        if(getUnit(position)->getType() != wasted)
        {
            return true;
        }
    }
    return false;
}

void Horde::evolve(const int position)
{
    zombie* evolving = Head;
    zombie* next   = nullptr;
    int lvl = 0;
    
    if (position == 0)
    {
        lvl = evolving->getLvl();
        next = evolving->getNext();
        delete evolving;
        Head = new class crasher(lvl);
        Head->setNext(next);
    }
    else
    {
        zombie* priv   =  Head;
        for (int i = 0; i<position-1; i++)
        {
            priv = priv->getNext();
        }
        evolving = priv->getNext();
        lvl = evolving->getLvl();
        next = evolving->getNext();
        delete evolving;
        evolving = new class crasher(lvl);
        priv->setNext(evolving);
        evolving->setNext(next);
    }
    
}

void Horde::swap(int position_1, int position_2)
{
    if (position_1 != position_2)
    {
        zombie* aloc_1 = Head;
        zombie* aloc_2 = Head;
        zombie* next_1 = nullptr;
        zombie* next_2 = nullptr;
        if (position_1 != position_2)
        {
            if (position_1 > position_2)
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
                    zombie* prev = Head;
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
                    zombie* prev_1 = Head;
                    zombie* prev_2 = Head;
                    zombie* next_2;
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
                if(position_2+1 == count)
                {
                    Tail = getUnit(count-1);
                }
            }
        }
    }
}

zombie* Horde::getTail() const
{
    return Tail;
}

void Horde::randomize()
{
    if (count>1)
    {
        int COUNT = 0;
        bool last = false;
        if (count % 2 == 1)
        {
            COUNT = (count-1)/2;
            last = true;
        }
        else
        {
            COUNT = count/2;
            last = false;
        }
        srand(unsigned(time(NULL)));
        
        int a = 0;
        
        for (int i = 0; i<COUNT; i++)
        {
            a = rand()%(COUNT)+i+1;
            swap(i, a);
        }
        if (last)
        {
            a = rand()%(count-1);
            swap(a, count-1);
        }
    }
}

zombie* Horde::getUnit(const int Position) const
{
        zombie* aloc = Head;
        
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

zombie* Horde::getHead() const
{
    return Head;
}

void Horde::addWalker(const int LVL)
{
    
    int lvl = LVL;
    if (lvl > 25)
    {
        lvl = 25;
    }
    if(count==0)
    {
        Head = new class walker(lvl);
        Tail = Head;
    }
    else
    {
        zombie* New = new class walker(lvl);
        Tail->setNext(New);
        Tail = Tail->getNext();
    }
    count ++;
}

void Horde::addLurker(const int LVL)
{
    
    int lvl = LVL;
    if (lvl > 25)
    {
        lvl = 25;
    }
    if(count==0)
    {
        Head = new class lurker(lvl);
        Tail = Head;
    }
    else
    {
        zombie* New = new class lurker(lvl);
        Tail->setNext(New);
        Tail = Tail->getNext();
    }
    count ++;
}

void Horde::addBasher(const int LVL)
{
    int lvl = LVL;
    if (lvl > 25)
    {
        lvl = 25;
    }
    if(count==0)
    {
        Head = new class basher(lvl);
        Tail = Head;
    }
    else
    {
        zombie* New = new class basher(lvl);
        Tail->setNext(New);
        Tail = Tail->getNext();
    }
    count ++;
}

void Horde::addCrasher(const int LVL)
{
    int lvl = LVL;
    if (lvl > 25)
    {
        lvl = 25;
    }
    if(count==0)
    {
        Head = new class crasher(lvl);
        Tail = Head;
    }
    else
    {
        zombie* New = new class crasher(lvl);
        Tail->setNext(New);
        Tail = Tail->getNext();
    }
    count ++;
}

int Horde::getCount() const
{
    return count;
}

void Horde::setNumberOfWaves(const int i)
{
    NumberOfWaves = i;
}

void Horde::addGhoul(const int LVL)
{
    
    int lvl = LVL;
    if (lvl > 25)
    {
        lvl = 25;
    }
    if(count==0)
    {
        Head = new class ghoul(lvl);
        Tail = Head;
    }
    else
    {
        zombie* New = new class ghoul(lvl);
        Tail->setNext(New);
        Tail = Tail->getNext();
    }
    count ++;
}

void Horde::addLeaper(const int LVL)
{
    
    int lvl = LVL;
    if (lvl > 25)
    {
        lvl = 25;
    }
    if(count==0)
    {
        Head = new class leaper(lvl);
        Tail = Head;
    }
    else
    {
        zombie* New = new class leaper(lvl);
        Tail->setNext(New);
        Tail = Tail->getNext();
    }
    count ++;
}