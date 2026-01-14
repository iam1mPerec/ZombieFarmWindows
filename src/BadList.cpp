#include <iostream>
#include "BadList.h"

using namespace std;

BadList::BadList(dialogBox &Box):
Head(nullptr),
Box(Box),
Current(nullptr),
count(0)
{
}
void BadList::hire()
{
    if(count==0)
    {
        Head = new farmer();
        Current = Head;
    }
    else
    {
        Current->fellow = new farmer();
        Current = Current->fellow;
    }
    
    Current->fellow = Head;
    count ++;
}
