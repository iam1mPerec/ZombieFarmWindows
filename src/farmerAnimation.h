#pragma once
#include "Farmer.h"
#include "field.h"
#include "resources.h"
#include "events_list.h"

enum action
{
    chill,
    plant,
    gather
};

class farmerAnimation
{
    action tsup;
    bool back;
    bool firstrun;
    bool visible;
    int Y;
    int X;
    int w8;
    int waiting;
    char ch;
    int x1;
    int x2;
    int y1;
    int y2;
    char** screen;
    enum plants plant;
    farmer* farmboy;
    dialogBox Dial;
    events_list& list;
    resources& Res;
    field& MyField;
    
public:
    farmerAnimation(char** M, field& MField, events_list& list, resources& Res, dialogBox &dial);
    void show();
    void hide();
    void reveal();
    void startPlanting(const int X1, const int X2, const int Y1, const int Y2, enum plants Plant,farmer* farmboy);
    void startCollecting(farmer* farmboy);
    void glowing();
    void resetVar();
    void seeder();
    void plantSelector();
    void createSector();
    int getDone() const;
};
