#pragma once
#include "eControls.h"

class SideMenu
{
    int sx;
    int sy;
    char ** ar;
    int option;
    int CurentNumberOfOptions;
    const int NumberOfOptions;
    char ** options;
    int menuOption;
    
public:
    SideMenu();
    int get_sx() const;
    int get_sy() const;
    int getMenuOption() const;
    int getOption() const;
    char** get_screen() const;
    void midler(const int position, const char name[]);
    void midler(const int num, char **name);
    void selector(const int num);
    void clearSelector();
    void slider(const eControls controls);
    void setOption(const int i);
    void setCurentNumberOfOptions();
    void clearOptions();
    void setMenuOption(const int i);
    void option_main();
    void option_healing();
    void option_planting();
    void option_building();
    void option_working();
    void option_slashing();
    void option_quiting();
    void option_attack();
    void option_selecting();
    void option_lvling();
    void option_upgrading();
    void option_shop();
    void option_battle();
    void option_buy();
    void option_sell();
    void option_swap();
    void option_amount();
    void option_equip();
    void addLvl(char* text,const int lvl);
    void option_abilities(const int type, const int ability_1, const int ability_2, const int ability_3, const int ability_4,
                          const int ability_5);
    void clear();
};
