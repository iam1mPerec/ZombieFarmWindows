#pragma once
#include "Farmer.h"

class GoodList
{
    farmer * Head;
    farmer * Tail;
    int count;
    
public:
    
    GoodList();
    int getcount() const;
    void death(const int number);
    void massDeath();
    void hire();
    farmer * checkForFreeFarmer();
    int freeFarmers();
};

//death - полное удаление фермера в случаи его смерти
//hire - найм фермера
//fire - выгнать фермера переместив его в черный список