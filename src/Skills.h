#pragma once

class Skills
{
    int splashDmg;
    
    int stun;
    int stunCount;
    
    int pirs;
    int bleedCount;
    
    int crit;
    int critDmg;
    
public:
    Skills();
    void addSkills(const int SplashDmg, const int Stun, const int StunCount,
                   const int Bleed, const int BleedCount, const int Crit, const int CritDmg);
    
    void setSplashDmg(const int ammount);
    void setStunChance(const int ammount);
    void setCritChance(const int ammount);
    void setPirsDmg(const int ammount);
    
    int getSplash()     const;
    int getStun()       const;
    int getPirs()      const;
    int getCrit()       const;
    
    int stuned()      const;
    int crited()      const;
};