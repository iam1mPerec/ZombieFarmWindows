#include <iostream>
#include "GoodList.h"

using namespace std;

GoodList::GoodList():
Head(nullptr),
Tail(nullptr),
count(0)
{
}

void GoodList::hire()
{
    if(count==0)
    {
        Head = new farmer();
        Tail = Head;
    }
    else
    {
        Tail->fellow = new farmer();
        Tail = Tail->fellow;
    }
    
    Tail->fellow = nullptr;
    count ++;
}

void GoodList::death(const int number)
{
    if (number<count)
    {
        farmer * ptr = Head;
        for (int i = 0; i<number; i++)
        {
            ptr = ptr->fellow;
        }
        if (ptr == Head)
        {
            Head = ptr->fellow;
            delete ptr;
        }
        else
        {
            farmer * ptr2 = ptr->fellow;
            ptr->fellow = ptr2->fellow;
            if (ptr2 == Tail)
            {
                Tail = ptr;
            }
            delete ptr2;
        }
        count--;
    }
}

void GoodList::massDeath()
{
    for (int i = count; i>0; i--)
    {
        death(i);
    }
    count = 0;
}
int GoodList::getcount() const
{
    return count;
}
int GoodList::freeFarmers()
{
    farmer * ptr = Head;
    int l = 0;
    
    for (int i = 0; i<count; i++)
    {
        if (ptr->getbusiness() == false)
        {
            l++;
        }
        ptr = ptr->fellow;
    }
    return l;
}

farmer* GoodList::checkForFreeFarmer()
{
  if (!freeFarmers())
  {
      return nullptr;
  }
  else
  {
      farmer * ptr = Head;
      while(ptr->getbusiness())
      {
          ptr = ptr->fellow;
      }
      return ptr;
}
}