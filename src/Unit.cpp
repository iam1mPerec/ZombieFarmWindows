#include <iostream>
#include "Unit.h"
#include "str.h"

using namespace std;

unit::unit():
hp(0),
atk(0),
lvl(0),
exp(0),
maxExp(0),
maxLVL(0),
shilds(false),
maxHp(0),
priority(0),
type(title::untitled),
Next(nullptr),
turn(1),
maxTurns(1),
alive(false),
blinck(0)
{
    create();
}

unit::unit(const enum title Type):
hp(0),
atk(0),
lvl(0),
exp(0),
maxExp(0),
maxLVL(0),
shilds(false),
maxHp(0),
priority(0),
Next(nullptr),
turn(1),
maxTurns(1),
alive(false),
type(Type),
blinck(0)
{
    create();
}

int unit::Difference(const int count)      const
{
    int Difference = (((hp*100)/maxHp)*count)/100;
    
    return Difference;
}

helmet* unit::equipHelmet(helmet * Helm)
{
    helmet* HELMET = equipment.getHelmet();
    if (HELMET)
    {
        hp -= Difference( HELMET->getHp());
        buff.setMaxHp   (-HELMET->getHp());
        buff.setDef     (-HELMET->getDef());
        buff.setPriority(-HELMET->getPriority());
    }
    if (Helm)
    {
        buff.setMaxHp   (Helm->getHp());
        hp += Difference(Helm->getHp());
        buff.setDef     (Helm->getDef());
        buff.setPriority(Helm->getPriority());
    }
    stat();
    draw();
    return equipment.equipHelmet(Helm);
}

chest* unit::equipChest(chest * Chest)
{
    chest* CHEST = equipment.getChest();
    if (CHEST)
    {
        hp -= Difference( CHEST->getHp());
        buff.setMaxHp   (-CHEST->getHp());
        buff.setDef     (-CHEST->getDef());
    }
    if (Chest)
    {
        buff.setMaxHp   (Chest->getHp());
        hp += Difference(Chest->getHp());
        buff.setDef     (Chest->getDef());
    }
    stat();
    draw();
    return equipment.equipChest(Chest);
}

gloves* unit::equipGloves(gloves * Gloves)
{
    gloves* GLOVES = equipment.getGloves();
    
    if (GLOVES)
    {
        hp -= Difference( GLOVES->getHp());
        buff.setMaxHp   (-GLOVES->getHp());
        buff.setDef     (-GLOVES->getDef());
    }
    if (Gloves)
    {
        buff.setMaxHp   (Gloves->getHp());
        hp += Difference(Gloves->getHp());
        buff.setDef     (Gloves->getDef());
    }
    stat();
    draw();
    return equipment.equipGloves(Gloves);
}

bool unit::unUsed() const
{
    if (type != untitled && type != rookie && IsAlive())
    {
        return abilities.unUsedPoint();
    }
    else
    {
        return 0;
    }
}

boots* unit::equipBoots(boots * Boots)
{
    boots* BOOTS = equipment.getBoots();
    if (BOOTS)
    {
        hp -= Difference( BOOTS->getHp());
        buff.setMaxHp   (-BOOTS->getHp());
        buff.setDef     (-BOOTS->getDef());
    }
    if (Boots)
    {
        buff.setMaxHp   (Boots->getHp());
        hp += Difference(Boots->getHp());
        buff.setDef     (Boots->getDef());
    }
    stat();
    draw();
    return equipment.equipBoots(Boots);
}

weapon* unit::equipWeapon(weapon * Weapon)
{
    weapon* WEAPON = equipment.getWeapon();
    if (equipment.getWeapon())
    {
        buff.setAtk     (-WEAPON->getDmg());
        buff.setMaxTurns(-WEAPON->getTurns());
        skills.setCritChance(-WEAPON->getCrit());
        skills.setSplashDmg(-WEAPON->getSplash());
        skills.setStunChance(-WEAPON->getStun());
        skills.setPirsDmg(-WEAPON->getPirs());
    }
    if (Weapon)
    {
        buff.setAtk(Weapon->getDmg());
        buff.setMaxTurns(Weapon->getTurns());
        skills.setCritChance(Weapon->getCrit());
        skills.setSplashDmg(Weapon->getSplash());
        skills.setStunChance(Weapon->getStun());
        skills.setPirsDmg(Weapon->getPirs());
    }
    stat();
    draw();
    return equipment.equipWeapon(Weapon);
}

bool unit::IsAlive() const
{
    return alive;
}

bool unit::IsDamaged() const
{
    return (hp < maxHp);
}

int unit::getDamage() const
{
    return atk;
}

void unit::setShild()
{
    shilds = true;
    turnSetTo0();
    stat();
    draw();
}

void unit::resetShild()
{
    shilds = false;
    stat();
    draw();
}

void unit::setBleeding(const int Bleed, const int Dmg)
{
    debuff.setBleeding(Bleed, Dmg);
}

void unit::setStunned (const int Stun)
{
    debuff.setStunned(Stun);
}

int unit::getStuned()       const
{
    return skills.stuned();
}

int unit::getCrited()       const
{
    return skills.crited();
}

int unit::getBleeding()     const
{
    return debuff.getBleed();
}

int unit::getBleedingDmg()  const
{
    return debuff.getBleedCount() * debuff.getBleed();
}

int unit::getBleedingCount()  const
{
    return debuff.getBleedCount();
}

void unit::resetTurns()
{
    if (alive && type != untitled)
    {
        turn = maxTurns;
    }
}

int unit::getPriority() const
{
    return priority;
}

void unit::draw()
{
    if (type != untitled)
    {
        int HP = hp;
        
        for (int i = 0; i<LenOfNumbers(maxHp); i++)
        {
            pic[6][8-i] = ' ';
        }
        for (int i = 0; i<LenOfNumbers(hp); i++)
        {
            pic[6][8-i] = (char)((int)'0')+HP%10;
            HP /= 10;
        }
        if (alive)
        {
            int LVL = lvl;
            for (int i = 0; i<LenOfNumbers(lvl); i++)
            {
                pic[1][7-i] = (char)((int)'0')+LVL%10;
                LVL /= 10;
            }
            
            for (int i = 0; i<LenOfNumbers(999); i++)
            {
                pic[6][17-i] = ' ';
            }
            int DEF = deff;
            
            for (int i = 0; i<LenOfNumbers(deff); i++)
            {
                pic[6][17-i] = (char)((int)'0')+DEF%10;
                DEF /= 10;
            }
            int ATK = atk;
            for (int i = 0; i<LenOfNumbers(atk); i++)
            {
                pic[7][8-i] = (char)((int)'0')+ATK%10;
                ATK /= 10;
            }
            int EXP = exp;
            int bar = maxExp/12;
            for (int i = 0; i<EXP/bar; i++)
            {
                pic[8][i+7] = char(8);
            }
            if (abilities.unUsedPoint())
            {
                pic[7][17] = '\1';
            }
            else
            {
                pic[7][17] = ' ';
            }
        }
        else
        {
            pic[3][9]  = '^';
            pic[3][11] = '^';
        }
    }
}

void unit::revive()
{
    hp = 10;
    alive = true;
    stat();
    draw();
    pic[3][9]  = '\2';
    pic[3][11] = '\2';
}

int unit::getMaxTurns() const
{
    return maxTurns;
}

int unit::getLvl() const
{
    return lvl;
}

int   unit::getMaxHp()     const
{
    return maxHp;
}

int   unit::getDef()       const
{
    return deff;
}

void unit::picture()
{
    draw();
}
char unit::getPic(const int j, const int i) const
{
    return pic[j][i];
}

void unit::create()
{
    char array[10][22]=
    {   " ___________________ ",
        "| lvl               |",
        "|                   |",
        "|                   |",
        "|                   |",
        "|                   |",
        "| hp       def      |",
        "| atk      skill    |",
        "| exp               |",
        "|___________________|",
    };
    
    for (int j = 0; j<10; j++)
    {
        for (int i = 0; i<22; i++)
        {
            pic[j][i] = array[j][i];
        }
    }
}

int   unit::getSplash()    const
{
    return skills.getSplash();
}
int   unit::getCrit()      const
{
    return skills.getCrit();
}
int   unit::getStun()      const
{
    return skills.getStun();
}
int   unit::getPirs()      const
{
    return skills.getPirs();
}

int unit::getTurn() const
{
    return turn;
}

int unit::getType() const
{
    return type;
}

void unit::usedTurn()
{
    --turn;
}

void unit::turnSetTo0()
{
    turn = 0;
}

void unit::HpUp(const int factor)
{
    hp += factor;
    if (hp > maxHp)
    {
        hp = maxHp;
    }
    draw();
}

void unit::addBuff()
{
    atk      += buff.getAtk();
    deff     += buff.getDef();
    maxHp    += buff.getMaxHp();
    
    if (maxHp < hp)
    {
        hp = maxHp;
    }
    
    maxTurns += buff.getMaxTurns();
    priority += buff.getPriority();
}

void unit::stat()
{

}

int unit::getExp() const
{
    return exp;
}

int unit::gethealth() const
{
    return hp;
}

void unit::OverHeal()
{
    hp = maxHp;
}

int unit::missingHP()
{
    return maxHp - hp;
}

int unit::getBlinck() const
{
    return blinck;
}

void unit::setBlinck(const int count)
{
    blinck = count;
}

void unit::lvl_up()
{
    lvl++;
    stat();
    if (lvl>maxLVL)
    {
        lvl = maxLVL;
        exp = maxExp;
    }
    else
    {
        if (type == sniper)
        {
            buff.setAtk(abilities.getAbility(5)*5);
        }
        else if(type == tank)
        {
            buff.setDef(abilities.getAbility(3)*3  );
            buff.setMaxHp(abilities.getAbility(4)*10);
            buff.setAtk(abilities.getAbility(5)*5  );
        }
        
        abilities.addUnused();
        
        if (exp>maxExp)
        {
            exp -= maxExp;
            lvl_up();
        }
        
        hp = maxHp;
    }
    
    draw();
}

void unit::lvl_up_ability(const int ability)
{
    if (abilities.unUsedPoint())
    {
        switch (type)
        {
            case sniper:
                
                switch (ability)
            {
                case 1:
                    abilities.lvlUpAbility(1);
                    break;
                case 2:
                    abilities.lvlUpAbility(2);
                    skills.addSkills(0, 15, 0, 0, 0, 0, 0);
                    if (abilities.getAbility(2)%2 == 2)
                    {
                        skills.addSkills(0, 0, 1, 0, 0, 0, 0);
                    }
                    break;
                case 3:
                    abilities.lvlUpAbility(3);
                    skills.addSkills(0, 0, 0, 0, 0, 15, 30);
                    break;
                case 4:
                    abilities.lvlUpAbility(4);
                    skills.addSkills(10, 0, 0, 0, 0, 0, 0);
                    break;
                case 5:
                    abilities.lvlUpAbility(5);
                    buff.setAtk(lvl*5);
                    //увеличивает прирост атаки и увеличивает колличество ходов на 1 на 1,3 и 5 уровнях
                    if (abilities.getAbility(5)%2 == 1)
                    {
                        buff.setMaxTurns(1);
                    }
                    break;
                    
                    default:
                        break;
                }
                break;
            
            case tank:
                switch (ability)
            {
                case 1:
                    abilities.lvlUpAbility(1);
                    skills.addSkills(0, 15, 0, 0, 0, 0, 0);
                    if (abilities.getAbility(1)%2 == 0)
                    {
                        //на 2 и 4 уровне способность будет добавлять +1 к длительности стана
                        skills.addSkills(0, 0, 1, 0, 0, 0, 0);
                    }
                    break;
                case 2:
                    abilities.lvlUpAbility(2);
                    // +15% сплеш урона
                    skills.addSkills(15, 0, 0, 0, 0, 0, 0);
                    break;
                case 3:
                    //увеличивает прирост атрибутов при повышении уровня броня
                    abilities.lvlUpAbility(3);
                    buff.setDef(3*lvl);
                    break;
                case 4:
                    //увеличивает прирост атрибутов при повышении уровня здоровье
                    abilities.lvlUpAbility(4);
                    buff.setMaxHp(10*lvl);
                    hp += 10*lvl;
                    break;
                case 5:
                    //увеличивает прирост атрибутов при повышении уровня Атака
                    buff.setAtk(5*lvl);
                    abilities.lvlUpAbility(5);
                    break;
                    
                default:
                    break;
            }
                break;
            
            case healer:
                switch (ability)
            {
                case 1:
                    abilities.lvlUpAbility(1);
                    skills.addSkills(0, 0, 0, 25, 0, 0, 0);
                    if (abilities.getAbility(1)%2 == 1)
                    {
                        skills.addSkills(0, 0, 0, 0, 1, 0, 0);
                    }
                    break;
                case 2:
                    abilities.lvlUpAbility(2);
                    buff.setPriority(1);
                    if (abilities.getAbility(2)%2 == 1)
                    {
                        buff.setMaxTurns(1);
                    }
                    break;
                case 3:
                    abilities.lvlUpAbility(3);
                    break;
                case 4:
                    abilities.lvlUpAbility(4);
                    break;
                case 5:
                    abilities.lvlUpAbility(5);
                    break;
                    
                default:
                    break;
            }
                break;
                
            default:
                break;
        }
    }
    stat();
    draw();
}

void unit::blincking()
{
    if (IsAlive())
    {
        pic[3][9]  = '-';
        pic[3][11] = '-';
    }
}

void unit::fine()
{
    if (IsAlive())
    {
        pic[3][9]  = char(2);
        pic[3][11] = char(2);
    }
}

int unit::getAbility(const int ability) const
{
    return abilities.getAbility(ability);
}

void unit::damaged(const int DMG)
{
    int dmg = DMG - deff;
    {
        if (dmg < 3)
        {
            dmg = 3;
        }
    }
    hp -= dmg;
    if (hp <= 0)
    {
        alive = false;
        turn = 0;
        hp = 0;
    }
    draw();
}

void unit::setNext(unit* next)
{
    Next = next;
}

unit* unit::getNext()
{
    return Next;
}

void unit::add_exp (const int xp)
{
    exp += xp;
    while(exp>=maxExp && lvl<maxLVL)
    {
        exp -= maxExp;
        for (int i = 0; i<12; i++)
        {
            pic[8][7+i] = ' ';
        }
        lvl_up();
    }
    if (lvl>=maxLVL)
    {
        lvl = maxLVL;
        exp = maxExp;
    }
}

class weapon* unit::getWeapon() const
{
    return equipment.getWeapon();
}

class helmet* unit::getHelmet() const
{
    return equipment.getHelmet();
}
class chest* unit::getChest () const
{
    return equipment.getChest();
}
class gloves* unit::getGloves() const
{
    return equipment.getGloves();
}
class boots* unit::getBoots () const
{
    return equipment.getBoots();
}


