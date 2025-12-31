#include <iostream>
#include "Equip.h"
#include "buffs.h"

using namespace std;

Equip::Equip():
HElmet(nullptr),
CHest(nullptr),
GLoves(nullptr),
BOots(nullptr),
WEapon(nullptr)
{
    
}

class helmet* Equip::getHelmet() const
{
    return HElmet;
}

class chest * Equip::getChest () const
{
    return CHest;
}

class gloves* Equip::getGloves() const
{
    return GLoves;
}

class boots * Equip::getBoots () const
{
    return BOots;
}

weapon * Equip::getWeapon() const
{
    return WEapon;
}

helmet * Equip::equipHelmet(helmet *Helm)
{
    helmet* h = HElmet;
    HElmet = Helm;
    return h;
}

chest* Equip::equipChest(chest *Chest)
{
    chest* c = CHest;
    CHest = Chest;
    return c;
}

gloves* Equip::equipGloves(gloves *Gloves)
{
    gloves* g = GLoves;
    GLoves = Gloves;
    return g;
}

boots* Equip::equipBoots(boots *Boots)
{
    boots* b = BOots;
    BOots = Boots;
    return b;
}

weapon* Equip::equipWeapon(weapon *Weapon)
{
    weapon* w = WEapon;
    WEapon = Weapon;
    return w;
}