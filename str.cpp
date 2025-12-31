#include <iostream>
#include "str.h"

void strcpy_s(char* a,int l,const char* b)
{
    for(int i = 0; i<l; i++)
    {
        a[i]=b[i];
    }
}

void deflation(char* buff)
{
    int l = unsigned(strlen(buff));
    for (int i = 0; i<l; i++)
    {
        if(buff[i] == ' ')
        {
            buff [i] = '$';
        }
    }
}

void inflation(char* buff)
{
    int l = unsigned(strlen(buff));
    for (int i = 0; i<l; i++)
    {
        if(buff[i] == '$')
        {
            buff [i] = ' ';
        }
    }
}

bool equals(const char* Name,const char* sName)
{
    bool equals = false;
    int l = unsigned(strlen(Name));
    
    if (l < strlen(sName))
    {
        equals = false;
    }
    else
    {
        for (int i = 0; i<l; i++)
        {
            if (Name[i] == sName[i])
            {
                equals = true;
            }
            else
            {
                equals = false;
                i = l;
            }
        }
    }
    
    return equals;
}

void clean(char* buff, const int l)
{
    for (int i = 0; i < l; i++)
    {
        buff[i] = '\0';
    }
}
void clean(char* buff)
{
    int l = unsigned(strlen(buff));
    
    for (int i = 0; i < l; i++)
    {
        buff[i] = '\0';
    }
}

void addToString(char * buff, const char * string)
{
    int l = unsigned(strlen(string))+1;
    int k = unsigned(strlen(buff));
    
    if (k && string[0] != '%' && string[0] != ' ')
    {
        buff[k] = ' ';
        k++;
    }
    
    for (int i = 0; i < l; i++)
    {
        buff[k+i] = string[i];
    }
}


int LenOfNumbers(const int num)
{
    if (num == 0)
    {
        return 1;
    }
    else
    {
    int l = 0;
    int Num = num;
    
    while (Num)
    {
        l++;
        Num /=10;
    }
    
    return l;
    }
}