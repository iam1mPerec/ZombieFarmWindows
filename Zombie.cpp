#include "Zombie.h"
#include <iostream>
#include "str.h"

using namespace std;

zombie::zombie(zombies Type,const int Lvl):
type(blank),
Next(nullptr),
lvl(Lvl),
hp(0),
atk(0),
deff(0),
turn(1),
MaxTurns(1),
pirs(0),
splash(0),
priority(0),
vamp(0),
bash(0)
{
    char array[10][11]=
    {   " ________ ",
        "|        |",
        "|lvl     |",
        "|        |",
        "|        |",
        "|        |",
        "|hp      |",
        "|atk     |",
        "|deff    |",
        "|________|"
    };
    
    for (int j = 0; j<10; j++)
    {
        for (int i = 0; i<11; i++)
        {
            pic[j][i] = array[j][i];
        }
    }
}

zombie* zombie::getNext()
{
    return Next;
}

void zombie::usedTurn()
{
    if (type != wasted)
    {
        --turn;
    }
}

void zombie::damage(const int DMG)
{
    if (DMG >= 0)
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
            type = wasted;
            turn = 0;
        }
    }
    else
    {
       int dmg = abs(DMG);
        hp += dmg;
    }
    
    draw();
}

void zombie::resetTurns()
{
    if (type != wasted && type != blank)
    {
        turn = MaxTurns;
    }
}

void zombie::setAtk(const int Atk)
{
    atk += Atk;
    draw();
}

int zombie::getTurn() const
{
    return turn;
}

int zombie::getPriority() const
{
    return priority;
}

void  zombie::setNext(zombie* next)
{
    Next = next;
}

void zombie::draw()
{
    if (type != wasted)
    {
        int LVL = lvl;
        for (int i = 0; i<LenOfNumbers(lvl); i++)
        {
            pic[2][7-i] = (char)((int)'0')+LVL%10;
            if (LVL == 0)
            {
                pic[1][7-i] = ' ';
                i = 2;
            }
            LVL /= 10;
        }
        
        int HP = hp;
        for (int i = 0; i<LenOfNumbers(9999); i++)
        {
            pic[6][8-i] = ' ';
        }
        for (int i = 0; i<LenOfNumbers(hp); i++)
        {
            pic[6][8-i] = (char)((int)'0')+HP%10;
            HP /= 10;
        }
        int ATK = atk;
        for (int i = 0; i<LenOfNumbers(atk); i++)
        {
            pic[7][8-i] = (char)((int)'0')+ATK%10;
            ATK /= 10;
        }
        int DEF = deff;
        for (int i = 0; i<LenOfNumbers(deff); i++)
        {
            pic[8][8-i] = (char)((int)'0')+DEF%10;
            DEF /= 10;
        }
    }
    else
    {
        char selector[10][11] =
        {
            "          ",
            "          ",
            "          ",
            "   _____  ",
            "  /     $ ",
            " |  RIP  |",
            " |       |",
            " |_______|",
            "          ",
            "          "
        };
        for (int j = 0; j < 10 ; j++)
        {
            for (int i = 0; i < 11; i++)
            {
                if (selector[j][i] == '$')
                {
                    pic[j][i] = '\\';
                }
                else
                {
                    pic[j][i] = selector[j][i];
                }
            }
        }
    }
}

int zombie::getLvl() const
{
    return lvl;
}

void zombie::stunedOut()
{
    debuff.BeStunned();
}

void zombie::bleedOut()
{
    hp -= debuff.getBleedCount();
    if (hp <= 0)
    {
        type = wasted;
        turn = 0;
    }
    debuff.bleedOut();
    draw();
}

void zombie::setTurnsTo0()
{
    turn = 0;
}

void zombie::setBleeding(const int Bleed, const int Dmg)
{
    debuff.setBleeding(Bleed, Dmg);
}

void zombie::setStunned (const int Stun)
{
    debuff.setStunned(Stun);
}

int zombie::getStun()      const
{
    return debuff.getStun();
}

int zombie::getBleed()     const
{
    return debuff.getBleed();
}

int zombie::getBleedDmg()  const
{
    return debuff.getBleedCount() * debuff.getBleed();
}

int zombie::getBleedCount()  const
{
    return debuff.getBleedCount();
}

char  zombie::getPic(const int j, const int i) const
{
    return pic[j][i];
}

int zombie::getAttack() const
{
    return atk;
}

int zombie::getHp() const
{
    return hp;
}
bool zombie::getPirs() const
{
    return pirs;
}
bool zombie::getSplash() const
{
    return splash;
}
int zombie::getType() const
{
    return type;
}

