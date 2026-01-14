#pragma once
#include "event.h"
#include "work.h"
#include "plant.h"
#include "dialogBox.h"
#include "field.h"
#include "building.h"
#include "constructions.h"

class events_list
{
    event * Head;
    event * Tail;
    int count;
    
public:
    
    events_list();
    event * listing(const int l);
    event * getHead();
    
    void AddPlant(field& MField, char** M, const int Size, dialogBox& Box, enum plants plant_type);
    void AddPlant(field& MField, char** M, const int Size, dialogBox& Box, enum plants plant_type, int pday, int phour, int pmin);
    
    void AddBuilding(field &MField, farmer * f, dialogBox &Box,
                     structures building_type, constructions &possession, char** ar);
    void AddBuilding(field &MField, farmer * f, dialogBox &Box,
                     structures building_type, constructions &possession, char** ar, int pday, int phour, int pmin);
    
    void AddWork(farmer * f, dialogBox &Box, enum jobs type, resources &Res);
    void AddWork(farmer * f, dialogBox &Box, enum jobs type, resources &Res, int pday, int phour, int pmin);
    
    int getCount();
    void check4Dead();
    void deleteNode(event* name);
    bool check4(const char* Name) const;
};