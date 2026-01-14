#pragma once

class node
{
    char* PropName;
    int   PropValue;
    
    node* next;
    
public:
    node(char * pName, int pValue);
    node(char * pName);
};