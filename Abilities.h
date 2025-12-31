#pragma once

class abilities
{
    int UnUsedPoints;
    int Ability_1;
    int Ability_2;
    int Ability_3;
    int Ability_4;
    int Ability_5;
    const int MaxLvl;
    
public:
    bool unUsedPoint() const;
    int  getAbility(const int ability)  const;
    void  lvlUpAbility(const int ability);
    void addUnused();
    void addUnused(const int count);
    abilities();
    ~abilities();
};