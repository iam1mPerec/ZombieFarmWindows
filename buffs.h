#pragma once

class buffs
{
    int atk;
    int def;
    int maxHp;
    int maxTurns;
    int priority;
    
public:
    buffs();
    void setAtk(const int count);
    void setDef(const int count);
    void setMaxHp(const int count);
    void setMaxTurns(const int count);
    void setPriority(const int count);
    
    int getPriority() const;
    int getAtk() const;
    int getDef() const;
    int getMaxHp() const;
    int getMaxTurns() const;
};