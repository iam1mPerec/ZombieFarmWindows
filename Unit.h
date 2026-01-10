# pragma once
#include "buffs.h"
#include "Equip.h"
#include "Skills.h"
#include "DeBuff.h"
#include "titles.h"
#include "Abilities.h"

class unit
{
protected:
    unit* Next;
    const enum title type;
    char* name;
    int  hp;
    int  maxHp;
    int  maxExp;
    int  maxLVL;
    int  priority;
    int  deff;
    int  atk;
    int  exp;
    int  lvl;
    int  blinck;
    bool alive;
    
	Skills skills;
    buffs  buff;
    Equip  equipment;
    deBuff debuff;
	Abilities abilities;
    
    int turn;
    int maxTurns;
    bool shilds;
    char pic[10][22];
    
public:
    unit();
    unit(const enum title Type);
    virtual void  stat();
    virtual void create();
    
    void  revive();
    void  addBuff();
    
    class helmet* getHelmet() const;
    class chest*  getChest () const;
    class gloves* getGloves() const;
    class boots*  getBoots () const;
    class weapon* getWeapon() const;
    
    helmet* equipHelmet(helmet*);
    chest*  equipChest(chest*);
    gloves* equipGloves(gloves*);
    boots*  equipBoots(boots*);
    weapon* equipWeapon(weapon*);
    
    void  damaged(const int damage);
    void  add_exp(const int xp);
    void  draw();
    void  HpUp(const int factor);
    void  usedTurn();
    void  turnSetTo0();
    void  setBlinck(const int count);
    bool  IsAlive()     const;
    bool  IsDamaged()   const;
    int   getExp()      const;
    int   gethealth()   const;
    int   getType()     const;
    int   getLvl()      const;
    int   getPriority() const;
    int   getTurn()     const;
    
    int   getBlinck()     const;
    int   getMaxHp()     const;
    int   getDamage()    const;
    int   getDef()       const;
    int   getMaxTurns()  const;

    void setBleeding(const int Bleed, const int Dmg);
    void setStunned (const int Stun);
    
    
    int Difference(const int count) const;
    int getStuned()           const;
    int getCrited()           const;
    int getBleeding()         const;
    int getBleedingDmg()      const;
    int getBleedingCount()    const;
    
    int   getSplash()    const;
    int   getCrit()      const;
    int   getStun()      const;
    int   getPirs()      const;
    bool   unUsed()      const;
    
    void blincking();
    void fine();
    
    int   getAbility(const int ability) const;
    void  setShild();
    void  resetShild();
    void  resetTurns();
    void  OverHeal();
    int   missingHP();
    void  picture();
    char  getPic(const int j, const int i) const;
    void  lvl_up();
    void  lvl_up_ability(const int ability);
    void  setNext(unit* next);
    unit* getNext();
};