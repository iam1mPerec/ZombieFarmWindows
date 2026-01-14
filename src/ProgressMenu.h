#pragma once
#include "events_list.h"

class ProgressMenu
{
    char ** menu;
    char ** screen;
    
    int mx;
    int my;
    events_list &events;
    
public:
    
    ProgressMenu(char ** screen, events_list &list);
    void showMenu();
    void clear();
    void showProgress(int tick);
    void showTimer(int tick);
    int get_mx() const;
    int get_my() const;
    char** getMenu() const;
    ~ProgressMenu();
};