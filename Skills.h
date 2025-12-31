#pragma once

class skills
{
    int splashDmg;
    
    int stun;
    int stunDur;
    
    int pirs;
    int bleedDur;
    
    int crit;
    int critDmg;
    
public:
    skills();
    void addSkills(const int SplashDmg, const int Stun, const int StunDur,
                   const int Bleed, const int BleedDur, const int Crit, const int CritDmg);
    
    void setSplashDmg(const int ammount);
    void setStunChance(const int ammount);
    void setCritChance(const int ammount);
    void setPirsDmg(const int ammount);
    
    int getSplash()     const;
    int getStun()       const;
    int getPisrs()      const;
    int getCrit()       const;
    
    int stuned()      const;
    int crited()      const;
    int setBleading() const;
};