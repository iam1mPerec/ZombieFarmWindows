#include <iostream>
#include "UpGrade.h"

using namespace std;

UpGrade::UpGrade():
count(3),
Head(nullptr)
{
    unit* aloc = nullptr;
    aloc = new class tank();
    Head = aloc;
    unit* New = new class sniper();
    aloc->setNext(New);
    aloc = aloc->getNext();
    New = nullptr;
    New = new class healer();
    aloc->setNext(New);
}

unit* UpGrade::operator[](const int i)
{
    unit* aloc = Head;
    int l = i;
    if (l>count)
    {
        l=count;
    }
    for (int j = 0; j<l; j++)
    {
        aloc = aloc->getNext();
    }
    return aloc;
}