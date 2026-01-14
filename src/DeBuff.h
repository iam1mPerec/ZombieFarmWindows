#pragma once

class deBuff
{
    int stun;
    int bleedDmg;
    int bleedCount;
    
public:
    int getStun()       const;
    int getBleed()      const;
    int getBleedCount() const;
    
    void setStunned(const int Stun);
    void setBleeding(const int BleedDmg, const int BleedCount);
    
    void bleedOut();
    void BeStunned();
    
    deBuff();
};