#include <iostream>
#include "plant.h"
#include "str.h"

using namespace std;

plant::plant(field &MField,char** M,const int size, dialogBox &Box, enum plants type, int pday, int phour, int pmin):
event(),
matrix(nullptr),
MField(MField),
Box(Box),
cost(0),
option(type),
size(MField.getSize())
{
    create(MField, M,size, Box, type, pday, phour, pmin);
}

char ** plant::getMatrix()
{
    return matrix;
}

void plant::create(field &MField,char** M,const int Size, dialogBox &Box, enum plants type, int pday, int phour, int pmin)
{
    pDay  = pday;
    pHour = phour;
    pMin  = pmin;
    
    switch (type)
    {
        case potato:
            cost  = 1;
            reward = 2;
            break;
            
        case corn:
            cost   =  2;
            reward = -5;
            break;
            
        case tomato:
            cost  = 3;
            reward = 10;
            break;
            
        case carrot:
            cost  = 4;
            reward = 18;
            break;
            
        case pumpkin:
            cost  =    5;
            reward = -25;
            break;
            
        case cherry:
            cost  = 6;
            reward = 40;
            break;
            
        default:
            Box.AddQuote("Error! Wrong input!");
            break;
    }
    
    int l = unsigned(strlen(plants[type]))+1;
    name = new char [l];
    strcpy_s(name, l, plants[type]);
    
    if (pMin>59)
    {
        pMin = 59;
    }
    if (pHour>23)
    {
        pHour = 23;
    }
    if (pDay>30)
    {
        pDay = 30;
    }
    
    size = Size;
    
    matrix = new char * [Size];
    for (int i = 0; i<Size; i++)
    {
        matrix[i] = new char [Size];
    }
    
    for (int j = 0; j<Size; j++)
    {
        for (int i = 0; i<Size; i++)
        {
            matrix[j][i] = M[j][i];
            if(matrix[j][i] != ' ')
            {
                ammount++;
            }
        }
    }
    
    int num = ammount;
    char buff[] = {"Growing "};
    int length = unsigned(strlen(buff));
    
    strcpy_s(header, length, buff);
    
    header[length] = '(';
    
    int s = 0;
    while (num != 0)
    {
        s++;
        num = num/10;
    }
    
    s+=length;
    
    num = ammount;
    
    while (num!=0)
    {
        length ++;
        header[s] = (char)((int)'0')+num%10;
        num /= 10;
        s--;
    }
    length ++;
    header[length] = ')';
    
    for (int i = 0; i<strlen(name); i++)
    {
        header[length + 1 + i] = name[i];
    }
    
    length += strlen(name)+1;
    
    for (int i = length; i<y-SidePlank-3; i++)
    {
        header[i] = ' ';
    }
    
    for (int j = 0 , y = ((MField.getSize()*2-1) - size)/2; j<size; j++, y++)
    {
        for (int i = 0, x = ((MField.getSize()*2-1) - size)/2; i<size; i++, x++)
        {
            if (matrix[j][i] != ' ')
            {
                MField.getSquare()[y][x] = matrix[j][i];
            }
        }
    }
    MField.showField();
}

plant::plant(field &MField,char** M,const int Size, dialogBox &Box, enum plants type):
event(),
matrix(nullptr),
MField(MField),
Box(Box),
cost(0),
option(type),
size(MField.getSize())
{
    int pday  = 0;
    int phour = 0;
    int pmin  = 0;
    
    switch (option)
    {
        case potato:
            pday  = 0;
            phour = 1;
            pmin  = 0;
            break;
            
        case corn:
            pday  = 0;
            phour = 2;
            pmin  = 30;
            break;
            
        case tomato:
            pday  = 0;
            phour = 4;
            pmin  = 0;
            break;
        case carrot:
            pday  = 0;
            phour = 7;
            pmin  = 0;
            break;
            
        case pumpkin:
            pday  = 0;
            phour = 10;
            pmin  = 35;
            break;
            
        case cherry:
            pday  = 0;
            phour = 15;
            pmin  = 0;
            break;
            
        default:
            Box.AddQuote("Error! Wrong input!");
            break;
    }
    create(MField, M,Size, Box, type, pday, phour, pmin);
}

int plant::getOption() const
{
    return option;
}

int plant::getAmmount()
{
    return ammount;
}

void plant::doneFalse()
{
    done = false;
}

void plant::triger()
{
    done = true;
    pDay  = 0;
    pHour = 0;
    pMin  = 0;

    for (int j = 0 , y = ((MField.getSize()*2-1) - size)/2; j<size; j++, y++)
    {
        for (int i = 0, x = ((MField.getSize()*2-1) - size)/2; i<size; i++, x++)
        {
            if(matrix[j][i] == '#')
            {
                MField.getSquare()[y][x] = '$';
            }
        }
    }
    Box.AddQuote("Crops are grown");
    MField.showField();
}

void plant::Del()
{
    for (int j = 0 , y = ((MField.getSize()*2-1) - size)/2; j<size; j++, y++)
    {
        for (int i = 0, x = ((MField.getSize()*2-1) - size)/2; i<size; i++, x++)
        {
            if(matrix[j][i] == '#')
            {
                MField.getSquare()[y][x] = ' ';
            }
        }
    }
    for (int i = 0; i<size; i++)
        delete [] matrix[i];
    delete [] matrix;
    delete [] name;
}

int plant::getReward()
{
    return reward;
}

bool plant::show_progress() const
{
    return done;
}

int plant::getCost()
{
    return cost;
}