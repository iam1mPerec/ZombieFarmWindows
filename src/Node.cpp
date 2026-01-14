#include "Node.h"
#include <iostream>

using namespace std;

node::node(char* pName, int pValue):
PropName(pName),
PropValue(pValue)
{
    
}

node::node(char* pName):
PropName(pName),
PropValue(0)
{
    
}