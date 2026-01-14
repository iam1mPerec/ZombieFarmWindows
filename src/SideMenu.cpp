#include <iostream>
#include "SideMenu.h"
#include "screen.h"
#include "keys.h"
#include "GMGameMenu.h"
#include "plants.h"
#include "buildings.h"
#include "jobs.h"
#include "talents.h"

using namespace std;

SideMenu::SideMenu():
sx(ScreenSize::x - ScreenSize::BottomPlank-1),
sy(ScreenSize::y - ScreenSize::SidePlank-1),
option(0),
NumberOfOptions(6),
menuOption(1),
CurentNumberOfOptions(6)
{
    options = new char * [NumberOfOptions];
    for (int i = 0; i<NumberOfOptions; i++)
    {
        options[i] = new char [sy];
    }
    
    ar = new char * [sx];
    for (int i = 0; i<sx; i++)
    {
        ar[i] = new char [sy];
    }
    clear();
}

void SideMenu::addLvl(char *text, const int lvl)
{
    int l = unsigned(strlen(text));
    text[l]   = '(';
    text[l+1] = lvl + (char)((int)'0');
    text[l+2] = ')';
    text[l+3] = '\0';
}

void SideMenu::option_abilities(const int type, const int ability_1, const int ability_2,
                                const int ability_3, const int ability_4, const int ability_5)
{
    switch (type)
    {
        case sniper:
            clearOptions();
            strcpy_s(options[0], sy, talents[ScaterShot]);
            strcpy_s(options[1], sy, talents[AimedShot]);
            strcpy_s(options[2], sy, talents[SharpEye]);
            strcpy_s(options[3], sy, talents[BurstingShot]);
            strcpy_s(options[4], sy, talents[DeathBlow]);
            break;
        case healer:
            clearOptions();
            strcpy_s(options[0], sy, talents[Gorge]);
            strcpy_s(options[1], sy, talents[QuickHands]);
            strcpy_s(options[2], sy, talents[Heal]);
            strcpy_s(options[3], sy, talents[MassHeal]);
            strcpy_s(options[4], sy, talents[Revive]);
            break;
        case tank:
            clearOptions();
            strcpy_s(options[0], sy, talents[Bash]);
            strcpy_s(options[1], sy, talents[Smash]);
            strcpy_s(options[2], sy, talents[Toughness]);
            strcpy_s(options[3], sy, talents[Stamina]);
            strcpy_s(options[4], sy, talents[Strength]);
            break;
            
        default:
            break;
    }
    
    addLvl(options[0], ability_1);
    addLvl(options[1], ability_2);
    addLvl(options[2], ability_3);
    addLvl(options[3], ability_4);
    addLvl(options[4], ability_5);
    
    strcpy_s(options[5], sy, "Exit");
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
    selector(option);
}

void SideMenu::clearOptions()
{
    for (int j = 0; j<NumberOfOptions; j++)
    {
        for (int i = 0; i<sy; i++)
        {
            options[j][i] = ' ';
        }
    }
    
    for (int i = 0; i<NumberOfOptions; i++)
    {
        options[i][0] = '$';
    }
}

void SideMenu::setCurentNumberOfOptions()
{
    int j = 0;
    for (int i = 0; i<NumberOfOptions; i++)
    {
        if(options[i][0] != '$')
        {
            j++;
        }
    }
    CurentNumberOfOptions = j;
}

void SideMenu::option_main()
{
    clearOptions();
    strcpy_s(options[0], sy, "Planting");
    strcpy_s(options[1], sy, "Building");
    strcpy_s(options[2], sy, "Activities");
    strcpy_s(options[3], sy, "Troops");
    strcpy_s(options[4], sy, "Save");
    strcpy_s(options[5], sy, "Exit");
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
        selector(option);
}

void SideMenu::setOption(const int i)
{
    option = i;
}

void SideMenu::option_attack()
{
    clearOptions();
    strcpy_s(options[0], sy, "Attack");
    strcpy_s(options[1], sy,"Skills");
    strcpy_s(options[2], sy,"Items");
    strcpy_s(options[3], sy,"Protect");
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
    selector(option);
}

void SideMenu::option_planting()
{
    clearOptions();
    strcpy_s(options[0], sy, plants[0]);
    strcpy_s(options[1], sy, plants[1]);
    strcpy_s(options[2], sy, plants[2]);
    strcpy_s(options[3], sy, plants[3]);
    strcpy_s(options[4], sy, plants[4]);
    strcpy_s(options[5], sy, plants[5]);
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
    selector(option);
}
void SideMenu::option_building()
{
    clearOptions();
    strcpy_s(options[0], sy, buildings[fence]);
    strcpy_s(options[1], sy, buildings[tunel]);
    strcpy_s(options[2], sy, buildings[house]);
    strcpy_s(options[3], sy, buildings[tent]);
    strcpy_s(options[4], sy, buildings[barracks]);
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
    selector(option);
}
void SideMenu::option_working()
{
    clearOptions();
    strcpy_s(options[0], sy, jobs[chop]);
    strcpy_s(options[1], sy, jobs[adventure]);
    strcpy_s(options[2], sy, jobs[collect]);
    strcpy_s(options[3], sy, jobs[shop]);
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
    selector(option);
}

void SideMenu::option_healing()
{
    clearOptions();
    strcpy_s(options[0], sy," ");
    strcpy_s(options[1], sy, "Choose");
    strcpy_s(options[2], sy, "who would you like");
    strcpy_s(options[3], sy, "to heal");
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
}

void SideMenu::option_quiting()
{
    clearOptions();
    strcpy_s(options[0], sy, "Yes");
    strcpy_s(options[1], sy, "No");
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
    selector(option);
}

void SideMenu::option_shop()
{
    clearOptions();
    strcpy_s(options[0], sy, "Buy");
    strcpy_s(options[1], sy, "Sell");
    strcpy_s(options[2], sy, "Hire Farmers");
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
    selector(option);
}

void SideMenu::option_amount()
{
    clearOptions();
    strcpy_s(options[0], sy, "100"   );
    strcpy_s(options[1], sy, "250"   );
    strcpy_s(options[2], sy, "500"   );
    strcpy_s(options[3], sy, "1 000" );
    strcpy_s(options[4], sy, "5 000" );
    strcpy_s(options[5], sy, "10 000");
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
    selector(option);
}

void SideMenu::option_buy()
{
    clearOptions();
    strcpy_s(options[0], sy, "Wood"   );
    strcpy_s(options[1], sy, "Seeds"  );
    strcpy_s(options[2], sy, "Food"   );
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
    selector(option);
}

void SideMenu::option_sell()
{
    clearOptions();
    strcpy_s(options[0], sy, "Wood" );
    strcpy_s(options[1], sy, "Seeds");
    strcpy_s(options[2], sy, "Food" );
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
    selector(option);
}

void SideMenu::option_equip()
{
    clearOptions();
    strcpy_s(options[0], sy, " " );
    strcpy_s(options[1], sy, "Select");
    strcpy_s(options[2], sy, "A unit" );
    strcpy_s(options[3], sy, "That you wish");
    strcpy_s(options[4], sy, "To equip");
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
}

void SideMenu::option_battle()
{
    clearOptions();
    strcpy_s(options[0], sy, "Find Zombies" );
    strcpy_s(options[1], sy, "Rearrange");
    strcpy_s(options[2], sy, "lvl Up" );
    strcpy_s(options[3], sy, "Feed Units");
    strcpy_s(options[4], sy, "Hire Units");
    strcpy_s(options[5], sy, "Equip");
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
    selector(option);
}

void SideMenu::option_selecting()
{
    clearOptions();
    strcpy_s(options[0], sy, " ");
    strcpy_s(options[1], sy, " ");
    strcpy_s(options[2], sy, "Selection is in");
    strcpy_s(options[3], sy, "progress");
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
}

void SideMenu::option_swap()
{
    clearOptions();
    strcpy_s(options[0], sy, " ");
    strcpy_s(options[1], sy, "Select 2 cards");
    strcpy_s(options[2], sy, "To swap them");
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
}

void SideMenu::option_slashing()
{
    clearOptions();
    strcpy_s(options[0], sy," ");
    strcpy_s(options[1], sy, "select an enemy.");
    strcpy_s(options[2], sy, "the one you");
    strcpy_s(options[3], sy, "dislike");
    strcpy_s(options[4], sy, "The most");
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
}

void SideMenu::option_upgrading()
{
    clearOptions();
    strcpy_s(options[0], sy, " ");
    strcpy_s(options[1], sy, "Select a unit     ");
    strcpy_s(options[2], sy, "With a skill point");
    strcpy_s(options[3], sy, "To upgrade him    ");
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
}

void SideMenu::option_lvling()
{
    clearOptions();
    strcpy_s(options[0], sy, " ");
    strcpy_s(options[1], sy, "Select new class");
    strcpy_s(options[2], sy, "Tank sniper");
    strcpy_s(options[3], sy, "Or Medic");
    setCurentNumberOfOptions();
    for (int i = 0; i<CurentNumberOfOptions; i++)
    {
        midler(i, options);
    }
}

int SideMenu::getMenuOption() const
{
    return menuOption;
}

void SideMenu::clear()
{
    for(int j = 0; j<sx; j++)
    {
        for (int i = 0; i<sy; i++)
        {
            ar[j][i] = ' ';
        }
    }
}

int SideMenu::get_sx() const
{
    return sx;
}
int SideMenu::get_sy() const
{
    return sy;
}
char** SideMenu::get_screen() const
{
    return ar;
}

void SideMenu::midler(const int position, const char name[])
{
    for (int i = 0; i<strlen(name); i++)
    {
        ar[position][i+(sy/2-unsigned(strlen(name))/2)] = name[i];
    }
}



void SideMenu::midler(const int num, char **name)
{
    for (int i = 0; i<strlen(name[num]); i++)
    {
        ar[num*2+2][(sy-unsigned(strlen(name[num])))/2+i] = name[num][i];
    }
}

void SideMenu::selector(const int num)
{
    clearSelector();
    
    if(strlen(options[num])%2 == 1)
    {
        ar[num*2+2][(sy/2-unsigned(strlen(options[num]))/2)-1] = '<';
        ar[num*2+2][(sy/2+unsigned(strlen(options[num]))/2)+1] = '>';
    }
    else
    {
        ar[num*2+2][(sy/2-unsigned(strlen(options[num]))/2)-1] = '<';
        ar[num*2+2][(sy/2+unsigned(strlen(options[num]))/2)]   = '>';
    }
}

void SideMenu::clearSelector()
{
    for (int j = 1; j<sy-1; j++)
    {
        for(int i  = 1; i<sx-1; i++)
        {
            if(ar[i][j] == '<'||ar[i][j] == '>')
            {
                ar[i][j] = ' ';
            }
        }
    }
}

void SideMenu::slider(const eControls controls)
{ 
    if(controls == eControls::UP)
    {
        
        --option;
    
        if(option < 0)
        {
            option = CurentNumberOfOptions-1;
        }
        selector(option);
    }
    
    if (controls == eControls::DOWN)
    {
        
        ++option;
        
        if(option > CurentNumberOfOptions-1)
        {
            option = 0;
        }
        selector(option);
    }
}

void SideMenu::setMenuOption(const int i)
{
    setOption(0);
    menuOption = i;
}

int SideMenu::getOption() const
{
    return option;
}