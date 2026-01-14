#include <iostream>
#include "buffs.h"

using namespace std;

buffs::buffs():
atk(0),
def(0),
maxHp(0),
maxTurns(0),
priority(0)
{
    
}

void buffs::setAtk(const int count)
{
    atk += count;
}

void buffs::setDef(const int count)
{
    def += count;
}

void buffs::setMaxHp(const int count)
{
    maxHp += count;
}

void buffs::setMaxTurns(const int count)
{
    maxTurns += count;
}

void buffs::setPriority(const int count)
{
    priority += count;
}

int buffs::getPriority() const
{
    return priority;
}

int buffs::getAtk() const
{
    return atk;
}

int buffs::getDef() const
{
    return def;
}

int buffs::getMaxHp() const
{
    return maxHp;
}

int buffs::getMaxTurns() const
{
    return maxTurns;
}
