#pragma once
#include "event.h"
#include "jobs.h"
#include "Farmer.h"
#include "dialogBox.h"
#include "resources.h"


class work: public event
{
   enum jobs option;
   farmer * farmboy;
   dialogBox &Box;
   resources &Res;
    
public:
    farmer * getFarmer();
    work(farmer * f, dialogBox &Box, enum jobs type, resources &Res);
    work(farmer * f, dialogBox &Box, enum jobs type, resources &Res, int day, int hour, int min);
    void create(farmer * f, dialogBox &Box, enum jobs type, resources &Res);
    char** getName(const int i) const;
    void triger();
    void Del();
    int getOption() const;
};