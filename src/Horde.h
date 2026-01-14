#pragma once
#include "Zombie.h"

#include "Walker.h"
#include "Lurker.h"
#include "Ghoul.h"
#include "Basher.h"
#include "Crasher.h"
#include "Leaper.h"

class Horde
{
    zombie * Head;
    zombie * Tail;
    int count;
    int wave;
    int NumberOfWaves;
    int RewardMoney;
    int RewardExp;
    
public:
    Horde();
    int  getCount() const;
    int  getWave() const;
    void setWave(const int i);
    int  getNumberOfWaves() const;
    void setNumberOfWaves(const int i);
    int  getHighestPriority() const;
    int  getMoney() const;
    int  getExp() const;
    zombie* getTail() const;
    void swap(int position_1, int position_2);
    bool exists(const int position) const;
    int getAttackerPos() const;
    zombie* getAttacker() const;
    void deleteWave();
    void deleteAll();
    void resetWaves();
    void resetTurns();
    void randomize();
    void evolve(const int position);
    void setMoney(const int ammount);
    void setExp(const int ammount);
    void setMoney();
    void setExp();
    void addWalker (const int LVL);
    void addLurker (const int LVL);
    void addBasher (const int LVL);
    void addCrasher(const int LVL);
    void addGhoul  (const int LVL);
    void addLeaper (const int LVL);
    zombie* getUnit(const int position) const;
    zombie* getHead() const;
};