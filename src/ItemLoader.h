#pragma once
#include "item.h"
#include "ItemTypes.h"
#include "item.h"
#include "potion.h"
#include "kit.h"
#include "grenade.h"
#include "bomb.h"
#include "revive.h"
#include "bandages.h"
#include "weapon.h"
#include "helmet.h"
#include "chest.h"
#include "gloves.h"
#include "boots.h"
#include "parts.h"

class itemLoader
{
public:

    itemLoader();
    
    class helmet* helmet  (const int type);
    class chest * chest   (const int type);
    class gloves* gloves  (const int type);
    class boots * boots   (const int type);
    class weapon* weapon  (const int type);
    
    class helmet* helmet  (const char* Name);
    class chest * chest   (const char* Name);
    class gloves* gloves  (const char* Name);
    class boots * boots   (const char* Name);
    class weapon* weapon  (const char* Name);

    item* getRandomEquip();
    
    class potion  * potion  (const int type, const int Count);
    class kit     * kit     (const int type, const int Count);
    class bandages* bandages(const int type, const int Count);
    class grenade * grenade (const int type, const int Count);
    class bomb    * bomb    (const int type, const int Count);
    class revive  * revive  (const int type, const int Count);
    
    class potion  * potion  (const char* Name, const int Count);
    class kit     * kit     (const char* Name, const int Count);
    class bandages* bandages(const char* Name, const int Count);
    class grenade * grenade (const char* Name, const int Count);
    class bomb    * bomb    (const char* Name, const int Count);
    class revive  * revive  (const char* Name, const int Count);
    
    item* getRandomConsumable(const int MinR, const int MaxR);
    
    class item* head    ();
    class item* body    ();
    class item* hands   ();
    class item* feet    ();
    
    item* getRandomPart();
    
    int TypeFinder(const char * name, const char * path) const;
};