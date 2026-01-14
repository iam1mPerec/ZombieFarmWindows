#pragma once
#include "farmer.h"
#include "dialogBox.h"

class BadList
{
    farmer * Head;
    farmer * Current;
    dialogBox &Box;
    int count;
    
public:
        BadList(dialogBox &Box);
        void hire();
};