#pragma once
#include "event.h"
#include "buildings.h"
#include "constructions.h"
#include "events_list.h"

class building: public event
{
    structures option;
    
    char** screen;
    farmer * farmboy;
    field &MField;
    event * first;
    constructions &possession;
    dialogBox &Box;
    
public:
    building(field &MField, farmer * f, dialogBox &Box,
             structures building_type, constructions &possession, char** ar);
    building(field &MField, farmer * f, dialogBox &Box,
             structures building_type, constructions &possession, char** ar, int day, int hour, int minute);
    void create(field &MField, farmer * f, dialogBox &Box,
                        structures building_type, constructions &possession, char** ar, int day, int hour, int minute);
    void set_option(structures i);
    void Del();
    farmer * getFarmer();
    structures get_option();
    int getOption() const;
	bool show_progress() const override;
    void triger() override;
};