#pragma once
#include "helmet.h"
#include "chest.h"
#include "gloves.h"
#include "boots.h"
#include "weapon.h"

class Equip
{
    class helmet*  HElmet;
    class chest *  CHest;
    class gloves*  GLoves;
    class boots *  BOots;
    class weapon*  WEapon;

public:
    
    Equip();
    
    class helmet* getHelmet() const;
    class chest * getChest () const;
    class gloves* getGloves() const;
    class boots * getBoots () const;
    class weapon* getWeapon() const;
    
    helmet* equipHelmet(helmet* Helm);
    chest*  equipChest(chest* Chest);
    gloves* equipGloves(gloves* Gloves);
    boots*  equipBoots(boots* Boots);
    weapon* equipWeapon(weapon* Weapon);
    
    
};