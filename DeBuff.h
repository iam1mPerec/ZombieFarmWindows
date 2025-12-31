#pragma once

class deBuff
{
    int stun;
    int bleed;
    int bleedCount;
    
public:
    int getStun()       const;
    int getBleed()      const;
    int getBleedCount() const;
    
    void setStunned(const int Stun);
    void setBleeding(const int Bleed, const int Count);
    
    void bleedOut();
    void BeStunned();
    
    deBuff();
};