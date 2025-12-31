#pragma once
#include "event.h"
#include "plants.h"
#include "dialogBox.h"
#include "field.h"

class plant: public event
{
    char** matrix;
    enum plants option;
    int size;
    int ammount;
    int reward;
    int cost;
    field &MField;
    dialogBox &Box;
    
public:
    plant(field &MField,char** M,const int Size, dialogBox &Box, enum plants type);
    plant(field &MField,char** M,const int Size, dialogBox &Box, enum plants type, int pday, int phour, int pmin);
    void create(field &MField,char** M,const int Size, dialogBox &Box, enum plants type, int pday, int phour, int pmin);
    char *getName();
    int  getReward();
    int  getAmmount();
    int  getCost();
    int getOption() const;
    void Del();
    void triger();
    void doneFalse();
    bool show_progress() const;
    char ** getMatrix();
};
