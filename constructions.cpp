#include "constructions.h"
#include <iostream>
#include "screen.h"

using namespace std;

constructions::constructions(char ** screen):
road(false),
HomeSize(simple),
screen(screen),
maxHomeSize(spacious),
visible(true),
TentSize(noTent),
barracks(false),
maxTentSize(TentL)
{
    
   char ar[7][15] =
    {   "              ",
        "              ",
        " ___________  ",
        "/___________\\",
        "|  _    _   | ",
        "| |_|  |.|  | ",
        "|______|_|__| "
    };
    
    for (int j = 0; j<7; j++)
    {
        for (int i = 0; i<15; i++)
        {
            picHome[j][i] = ar[j][i];
        }
    }
    
    char agr[6][16] =
    {
        "       _       ",
        "      |_|      ",
        " ____|___|____ ",
        "/\\____________\\",
        "| | | |.| | | |",
        "|_|_|_|_|_|_|_|"
    };

    for (int j = 0; j<6; j++)
    {
        for (int i = 0; i<16; i++)
        {
            picBarrack[j][i] = agr[j][i];
        }
    }
    
    char array[6][25]=
    {   "     \6 \6",
        "     \6 \6",
        "     \6 \6",
        "     \6 \6",
        "     \6 \6 \6 \6 \6 \6 \6 \6 \6",
        "     \6 \6 \6 \6 \6 \6 \6 \6 \6"
    };
    
    for (int j = 0; j<6; j++)
    {
        for (int i = 0; i<23; i++)
        {
            picRoad[j][i] = array[j][i];
        }
    }
}

bool constructions::getBarracks() const
{
    return barracks;
}

int constructions::getMaxTentSize() const
{
    return maxTentSize;
}

int constructions::getTentSize() const
{
    return TentSize;
}

void constructions::buildRoad()
{
    if (visible)
    {
    int Y = x/2 - 4;
    for(int j = 0; j<6; j++)
    {
        int X = y/2+2;
        int i = 0;
        while(picRoad[j][i] != '\0')
        {
            screen[Y][X] = picRoad[j][i];
            i++;
            X++;
        }
        Y++;
    }
    }
    road = true;
}

void constructions::hide()
{
    visible = false;
}

void constructions::reveal()
{
    visible = true;
}

void constructions::buildHome()
{
    if (visible)
    {
        int Y = x/2 - 11;
        
        for(int j = 0; j<7; j++)
        {
            int X = y/2;
            int i = 0;
            while(picHome[j][i] != '\0')
            {
                screen[Y][X] = picHome[j][i];
                i++;
                X++;
            }
            Y++;
        }
    }
}

void constructions::buildBaracks()
{
    if (visible)
    {
        int Y = 10;
        for(int j = 0; j<6; j++)
        {
            int X = 15;
            int i = 0;
            while(picBarrack[j][i] != '\0')
            {
                screen[Y][X] = picBarrack[j][i];
                i++;
                X++;
            }
            Y++;
        }
    }
    barracks = true;
}

void constructions::buildTent()
{
    if (visible && TentSize)
    {
        int Y = x/2 - 9;
        for(int j = 0; j<5; j++)
        {
            int X = SidePlank-11;
            int i = 0;
            while(picTent[j][i] != '\0')
            {
                screen[Y][X] = picTent[j][i];
                i++;
                X++;
            }
            Y++;
        }
    }
}

void constructions::upgradeTentSize()
{
    switch(TentSize)
    {
        case noTent:
            TentSize = TentS;
        {
            char ar[5][12] =
            {
                " ",
                " ",
                " ",
                " /\\ ",
                "//\\\\ "
            };
            for (int j = 0; j<5; j++)
            {
                for (int i = 0; i<12; i++)
                {
                    picTent[j][i] = ar[j][i];
                }
            }
        }
            break;
            
        case TentS:
            TentSize = TentM;
        {
            char ar[5][12] =
            {
                " ",
                "     ",
                "  /\\ ",
                " /  \\ ",
                "/ /\\ \\ "
            };
            for (int j = 0; j<5; j++)
            {
                for (int i = 0; i<12; i++)
                {
                    picTent[j][i] = ar[j][i];
                }
            }
            break;
        }
            case TentM:
        {
            TentSize = TentL;
            char ar[5][12] =
        {
            " ",
            "   /\\    ",
            "  /  \\   ",
            " /    \\ ",
            "/  /\\  \\  "
        };
            for (int j = 0; j<5; j++)
            {
                for (int i = 0; i<12; i++)
                {
                    picTent[j][i] = ar[j][i];
                }
            }
            break;
    }
            default:
            {
                
            }
        }
    buildTent();
}

void constructions::upgradeHomeSize()
{
    switch(HomeSize)
    {
        case simple:
            HomeSize = roomy;
        {
            char ar[7][15] =
            {
                "              ",
                "  _________   ",
                " /         \\ ",
                "/___________\\",
                "|  _    _   | ",
                "| |_|  |.|  | ",
                "|______|_|__| "
            };
            for (int j = 0; j<7; j++)
            {
                for (int i = 0; i<15; i++)
                {
                    picHome[j][i] = ar[j][i];
                }
            }
        }
            break;
            
        case roomy:
            HomeSize = spacious;
        {
            char ar[7][15] =
            {
                "   _______    ",
                "  /       \\  ",
                " /         \\ ",
                "/___________\\",
                "|  _    _   | ",
                "| |_|  |.|  | ",
                "|______|_|__| "
            };
            for (int j = 0; j<7; j++)
            {
                for (int i = 0; i<15; i++)
                {
                    picHome[j][i] = ar[j][i];
                }
            }
        }
            break;
            
        case spacious:
            HomeSize = spacious;
            break;
    }
    buildHome();
}

bool constructions::getRoad() const
{
    return road;
}
int  constructions::getHouseSize() const
{
    return HomeSize;
}
int  constructions::getMaxHouseSize() const
{
    return maxHomeSize;
}