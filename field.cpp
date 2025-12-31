#include <iostream>
#include "field.h"
#include "GMGameMenu.h"
#include "screen.h"

using namespace std;

field::field(char** ar):
init_x(SidePlank/2),
init_y(BottomPlank/2),
array(ar),
square(nullptr),
oldSize(0),
field_size(Small),
maxSize(Huge),
visible(true)
{
    nSquare();
}

void field::hide()
{
    visible = false;
}

void field::reveal()
{
    visible = true;
}

void field::upgrade()
{
    DestroyFence();
    oldSize = field_size;
    ChangeFieldSize();
    nSquare();
    BuildFence();
}

char ** field::getSquare()
{
    return square;
}

int field::getSize()
{
    return field_size;
}

void field::showField()
{
    if (visible)
    {
    int shift = field_size - 1;
    for (int j = init_y - shift, h = 0; j<init_y+shift+1; j++, h++)
    {
        for (int i = init_x - shift, l = 0; i<init_x+shift+1; i++, l++)
        {
            array[j][i] = square[h][l];
        }
    }
    }
}

bool field::checkForPlace(const int j,const int i)
{
    if(square[j][i] == ' ')
    {
        return true;
    }
    else
    {
        return false;
    }
}

void field::nSquare()
{

    if (square != nullptr)
    {
        char** oldSquare = square;
        
        square = nullptr;
   
        int h = field_size*2 - 1;
        square = new char * [h];
        for (int i = 0; i<h; i++)
        {
            square[i] = new char [h];
        }
        
        for (int j = 0; j<h; j++)
        {
            for (int i = 0; i<h; i++)
            {
                square[j][i] = ' ';
            }
        }
        
        int difference = field_size - (oldSize);
        
        for (int j = difference, oj = 0; j<oldSize+difference; j++, oj++)
        {
            for (int i = difference, oi = 0; i<oldSize+difference; i++, oi++)
            {
                square[j][i] = oldSquare[oj][oi];
            }
        }
        
        for (int i = 0; i<oldSize; i++)
        {
            delete [] oldSquare[i];
        }
        delete [] oldSquare;
    }
    else
    {
        int h = field_size*2 - 1;
        square = new char * [h];
        for (int i = 0; i<h; i++)
        {
            square[i] = new char [h];
        }
        
        for (int j = 0; j<h; j++)
        {
            for (int i = 0; i<h; i++)
            {
                square[j][i] = ' ';
            }
        }
        
    }
}

void field::BuildFence()
{
    if (visible)
    {
        for(int i = init_x - field_size+1; i<init_x + field_size; i++)
        {
           array[init_y - field_size][i] = '_';
        }
        for(int i = init_x - field_size; i<init_x + field_size; i++)
        {
            array[init_y + field_size][i] = '_';
        }
        for(int i = init_y - field_size+1; i<init_y + field_size+1; i++)
        {
            array[i][init_x - field_size] = '|';
        }
        for(int i = init_y - field_size+1; i<init_y + field_size+1; i++)
        {
            array[i][init_x + field_size] = '|';
        }
    }
}

void field::openGates()
{
    array[init_y+field_size][init_x]   = ' ';
    array[init_y+field_size][init_x+1] = ' ';
    array[init_y+field_size][init_x-1] = '/';
}

void field::closeGates()
{
    array[init_y+field_size][init_x]   = '_';
    array[init_y+field_size][init_x+1] = '_';
    array[init_y+field_size][init_x-1] = '_';
}

void field::DestroyFence()
{
        for(int i = init_x - field_size+1; i<init_x + field_size; i++)
        {
            array[init_y - field_size][i] = ' ';
        }
        for(int i = init_x - field_size; i<init_x + field_size; i++)
        {
            array[init_y + field_size][i] = ' ';
        }
        for(int i = init_y - field_size+1; i<init_y + field_size+1; i++)
        {
            array[i][init_x - field_size] = ' ';
        }
        for(int i = init_y - field_size+1; i<init_y + field_size+1; i++)
        {
            array[i][init_x + field_size] = ' ';
        }
        array[init_y+field_size][init_x-1]= ' ';
}

int field::getMaxSize() const
{
    return maxSize;
}

void field::ChangeFieldSize()
{
    switch(field_size)
    {
    case Small:
    field_size = Medium;
    break;
    case Medium:
    field_size = Large;
    break;
    case Large:
    field_size=Huge;
    break;
    }
}
