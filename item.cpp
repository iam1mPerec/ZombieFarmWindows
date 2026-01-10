#include <iostream>
#include "item.h"
#include "str.h"
using namespace std;

item::item(const itemType Type, const int Price,const int restr):
restriction(restr),
price(Price),
type(Type),
Next(nullptr)
{
    char Pic[5][14] =
    {
        " ___________ ",
        "|           |",
        "|           |",
        "|           |",
        "|___________|"
    };
    
    for (int j = 0; j<14; j++)
    {
        for (int i = 0; i<28; i++)
        {
            description[j][i] = '\0';
        }
    }
    
    for (int i = 0; i<20; i++)
    {
        name[i]  = '\0';
        title[i] = '\0';
    }
    
    for (int j = 0; j < 14; j++)
    {
        description[j][0] = '$';
    }
    
    char selling[] = {"Class:          Price: "};
    
    switch (restriction)
    {
        case 0:
        {
            char text[] = "None";
            int l = unsigned(strlen(text));
            for (int i = 0; i<l; i++)
            {
                selling[i+7] = text[i];
            }
            break;
        }
        case 1:
        {
            char text[] = "Rookie";
            int l = unsigned(strlen(text));
            for (int i = 0; i<l; i++)
            {
                selling[i+7] = text[i];
            }
            break;
        }
        case 2:
        {
            char text[] = "Tank";
            int l = unsigned(strlen(text));
            for (int i = 0; i<l; i++)
            {
                selling[i+7] = text[i];
            }
            break;
        }
        case 3:
        {
            char text[] = "Sniper";
            int l = unsigned(strlen(text));
            for (int i = 0; i<l; i++)
            {
                selling[i+7] = text[i];
            }
            break;
        }
        case 4:
        {
            char text[] = "Healer";
            int l = unsigned(strlen(text));
            for (int i = 0; i<l; i++)
            {
                selling[i+7] = text[i];
            }
            break;
        }
            
        default:
            break;
    }
    
    strcpy_s(description[13], selling);
    int l = unsigned(strlen(selling));

    int PRICE = Price;

    snprintf(&description[13][l], sizeof(description[1] - l), "%d", PRICE);
    for (int i = strlen(description[13]); i < 28; i++) {
        description[13][i] = ' ';
    }
    
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 14; i++)
        {
            pic[j][i] = Pic[j][i];
        }
    }
}

int item::getProperty() const
{
    return 0;
}

int item::addCount(const int Count)
{
    return 0;
}

void item::showCount()
{
    cleanCount();
    if(getCount())
    {
        int len = LenOfNumbers(getCount());

        int COUNT = getCount();

        for (int i = 0; i < len; i++)
        {
            pic[3][11 - i] = (char)((int)'0') + COUNT % 10;
            COUNT /= 10;
        }
    }
}

void item::cleanCount()
{
    pic[3][11] = ' ';
    pic[3][10] = ' ';
}

void item::setCount(const int n)
{
    
}

int item::getCount() const
{
    return 0;
}

char item::getTitle(const int i) const
{
    return title[i];
}

void item::setNext(item* next)
{
    Next = next;
}

void item::cleanTitle()
{
    for (int j = 0; j<14; j++)
    {
        if (description[j][0] == '$')
        {
            description[j][0] = ' ';
        }
    }
}

void item::consume()
{
}

int  item::getHp()        const
{
    return 0;
}
int  item::getDef()       const
{
    return 0;
}
int  item::getDmg()       const
{
    return 0;
}
int  item::getPriority()  const
{
    return 0;
}
int  item::getTurns()     const
{
    return 0;
}
int  item::getCrit()      const
{
    return 0;
}
int  item::getStun()      const
{
    return 0;
}
int  item::getSplash()    const
{
    return 0;
}
int  item::getPirs()      const
{
    return 0;
}

void item::craft()
{
    
}

void item::fillDescription(const char *Descript)
{
    bool stuffed = false;
    int l = unsigned(strlen(Descript));
    if (name[0] == '\0')
    {
        for (int i = 0; i<l; i++)
        {
            name[i] = Descript[i];
        }
    }
    for (int j = 0; j < 12; j++)
    {
        if (description[j][0] == '$')
        {
            int l = unsigned(strlen(Descript)) + 1;
            
            if (l > 28)
            {
                l = 28;
            }
            strcpy_s(description[j], l, Descript);
            stuffed = true;
            break;
        }
    }
    if (!stuffed)
    {
        for (int i = 0; i<3; i++)
        {
            if (description[9+i][15] == '\0')
            {
                int l = 15 - unsigned(strlen(description[9+i]));
                for (int j = 0; j<l; j++)
                {
                    addToString(description[9+i], " ");
                }
                addToString(description[9+i], Descript);
                stuffed = true;
                break;
            }
        }
    }
}

char * item::getPath()
{
    return nullptr;
}

item* item::getNext()
{
    return Next;
}

int item::getType() const
{
    return type;
}

void item::clearDescript()
{
    for (int j = 0; j<14; j++)
    {
        for (int i = 0; i<28; i++)
        {
            if (description[j][i] == '\0' || description[j][i] == '$')
            {
                description[j][i] = ' ';
            }
        }
    }
}

char item::getName(const int i) const
{
    return name[i];
}

int item::getPrice() const
{
    return price;
}

char item::getPic(int j, int i) const
{
    return pic[j][i];
}

char item::getDescript(int j, int i) const
{
    return description[j][i];
}

int item::getRestriction() const
{
    return restriction;
}

void item::fillName(const char *Name)
{
    int l = unsigned(strlen(Name));
    int len = 0;
    
    bool doubleName = false;
    
    for (int i = 0; i<l; i++)
    {
        if (name[i] != ' ')
        {
            pic[2][i+1] = Name[i];
            len++;
        }
        else
        {
            doubleName = true;
            len++;
            break;
        }
    }
    if (doubleName)
    {
        for (int i = 0; i<l-len; i++)
        {
            pic[3][i+1] = Name[i+len];
        }
    }
}

void item::fillTitle(const char* Title)
{
    const int l = unsigned(strlen(Title));
    
    for (int i = 0; i<l; i++)
    {
        pic[1][i+1] = Title[i];
        title[i]    = Title[i];
    }
}