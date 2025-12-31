#pragma once
#include "DeBuff.h"

enum zombies
{
    blank,
    walker,
    ghoul,
    lurker,
    basher,
    crasher,
    leaper,
    wasted
};

class zombie
{
protected:
    enum zombies type;
    zombie* Next;
    int  hp;
    int  atk;
    int  pirs;
    int  splash;
    int  priority;
    int  bash;
    int  deff;
    int  vamp;
    int  lvl;
    int  turn;
    int  MaxTurns;
    char pic[10][11];
    
    deBuff debuff;

public:
    zombie(zombies Type,const int lvl);
    
    void setBleeding(const int Bleed, const int Dmg);
    void setStunned (const int Stun);
    
    int getStun()       const;
    int getBleed()      const;
    int getBleedDmg()   const;
    int getBleedCount() const;
    
    void stunedOut();
    void bleedOut();
    
    virtual void draw();
    void resetTurns();
    void setTurnsTo0();
    void usedTurn();
    int  getTurn() const;
    int  getAttack() const;
    int  getHp() const;
    int  getType() const;
    bool getPirs() const;
    int  getLvl() const;
    bool getSplash() const;
    void setNext(zombie* next);
    void damage(const int dmg);
    zombie* getNext();
    int  getPriority() const;
    void setAtk(const int Atk);
    char  getPic(const int j, const int i) const;
};