#pragma once
#include <iostream>

enum talents
{
    ScaterShot,
    AimedShot,
    SharpEye,
    BurstingShot,
    DeathBlow,
    
    Gorge,
    QuickHands,
    Heal,
    MassHeal,
    Revive,
    
    Bash,
    Smash,
    Toughness,
    Stamina,
    Strength,
    
    numberOfAbilities
};

enum ability
{
    ability_1,
    ability_2,
    ability_3,
    ability_4,
    ability_5
};

class text_talents
{
    text_talents();
public:
const static char talents[numberOfAbilities][20];
};
const static char talents[numberOfAbilities][20] =
{
    "ScaterShot",
    "AimedShot",
    "SharpEye",
    "BurstingShot",
    "DeathBlow",
    
    "Gorge",
    "QuickHands",
    "Heal",
    "MassHeal",
    "Revive",
    
    "Bash",
    "Smash",
    "Toughness",
    "Stamina",
    "Strength"
};