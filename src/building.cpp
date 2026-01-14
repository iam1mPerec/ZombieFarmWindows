#include <iostream>
#include "building.h"
#include "str.h"

using namespace std;

building::building(field &MField, farmer * f, dialogBox &Box,
                   structures building_type, constructions &possession, char** ar):
farmboy(f),
option(building_type),
screen(ar),
MField(MField),
possession(possession),
Box(Box)
{
    farmboy->busy();
    
    int pday  = 0;
    int phour = 0;
    int pmin  = 0;
    
    switch (option)
    {
        case fence:
        {
            switch (MField.getSize())
            {
                case Small:
                    pday  = 0;
                    phour = 2;
                    pmin  = 30;
                    break;
                    
                case Medium:
                    pday  = 0;
                    phour = 5;
                    pmin  = 0;
                    break;
                    
                case Large:
                    pday  = 0;
                    phour = 10;
                    pmin  = 25;
                    break;
                    
                default:
                    break;
            }
            break;
            
        case tent:
            {
                switch (possession.getTentSize())
                {
                    case noTent:
                        pday  = 0;
                        phour = 2;
                        pmin  = 45;
                        break;
                        
                    case TentS:
                        pday  = 0;
                        phour = 5;
                        pmin  = 50;
                        break;
                        
                    case TentM:
                        pday  = 0;
                        phour = 7;
                        pmin  = 40;
                        break;
                        
                    default:
                        break;
                }
                break;
            }
        case tunel:
            pday  = 0;
            phour = 5;
            pmin  = 0;
            break;
            
        case barracks:
            pday  = 0;
            phour = 10;
            pmin  = 0;
            break;
            
        case house:
            {
                switch (possession.getHouseSize())
                {
                    case simple:
                        pday  = 0;
                        phour = 15;
                        pmin  = 0;
                        break;
                        
                    case roomy:
                        pday  = 0;
                        phour = 45;
                        pmin  = 0;
                        break;
                    default:
                        break;
                }
            }
            break;
        }
        default:
            break;
    }
    create(MField, f, Box, building_type, possession, ar, pday, phour, pmin);
}

void building::create(field &MField, farmer *f, dialogBox &Box, structures building_type, constructions &possession, char **ar, int day, int hour, int minute)
{
    farmboy->busy();
    
    pDay  = day;
    pHour = hour;
    pMin  = minute;
    
    for (int i = 0; i<y-SidePlank-3; i++)
    {
        header[i] = ' ';
    }
    
    int l = unsigned(strlen(buildings[building_type]))+1;
    name = new char [l];
    strcpy_s(name, l, buildings[building_type]);
    
    char buff[] = {"Building "};
    int length = unsigned(strlen(buff));
    
    strcpy_s(header, length, buff);
    
    for (int i = 0; i<strlen(name); i++)
    {
        header[length + i] = name[i];
    }
    
    length += strlen(name);
}

building::building(field &MField, farmer * f, dialogBox &Box,
                   structures building_type, constructions &possession, char** ar, int day, int hour, int minute):
farmboy(f),
option(building_type),
screen(ar),
MField(MField),
possession(possession),
Box(Box)
{
    create(MField, f, Box, building_type, possession, ar, day, hour, minute);
}

int building::getOption() const
{
    return option;
}

bool building::show_progress() const
{
    return !done;
}

void building::set_option(structures i)
{
    option = i;
}

structures building::get_option()
{
    return option;
}

void building::triger()
{
    done = true;
    farmboy->free();
    
    switch (option)
    {
        case fence:
            MField.upgrade();
            break;
            
        case tunel:
            possession.buildRoad();
            break;
            
        case house:
            possession.upgradeHomeSize();
            break;
            
        case tent:
            possession.upgradeTentSize();
            break;
            
        case barracks:
            possession.buildBaracks();
            break;
        default:
            break;
    }
    Box.AddQuote("Building is complete");
}
farmer * building::getFarmer()
{
    return farmboy;
}

void building::Del()
{
    delete [] name;
}