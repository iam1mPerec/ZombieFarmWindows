#pragma once
#include "Unit.h"
#include "Solder.h"
#include "Tank.h"
#include "Sniper.h"
#include "Healer.h"

class party
{
    unit * Head;
    const int count;
public:
    party();
    int rollcall() const;
    void swap     (const int y1, const int x1, const int y2, const int x2);
    unit* getUnit (const int J, const int I) const;
    unit* getUnit (const int position) const;
    unit* getAttacker() const;
    void addSolder(const int J, const int I, const int LVL, const int HP);
    void addTank  (const int J, const int I, const int LVL, const int HP);
    void addSniper(const int J, const int I, const int LVL, const int HP);
    void addHealer(const int J, const int I, const int LVL, const int HP);
    void addSolder(const int J, const int I, const int LVL);
    void addTank  (const int J, const int I, const int LVL);
    void addSniper(const int J, const int I, const int LVL);
    void addHealer(const int J, const int I, const int LVL);
    void blincker();
    bool allHealed();
    
    void addSolder(const int J, const int I);
    void addTank  (const int J, const int I);
    void addSniper(const int J, const int I);
    void addHealer(const int J, const int I);
    
    void allFine();
    void massRevive();
    void resetTurns();
    void drawAll();
    int  getCount () const;
    int  getAttackerPos () const;
    int  getHighestPriority() const;
    void addSolder();
};