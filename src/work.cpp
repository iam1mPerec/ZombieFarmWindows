#include <iostream>
#include "work.h"
#include "str.h"

using namespace std;

work::work(farmer * f, dialogBox &Box, enum jobs type, resources &Res):
event(),
farmboy(f),
Box(Box),
option(type),
Res(Res)
{
    create(f, Box, type, Res);
}

work::work(farmer * f, dialogBox &Box, enum jobs type, resources &Res, int day, int hour, int min):
event(),
farmboy(f),
Box(Box),
option(type),
Res(Res)
{
    create(f, Box, type, Res);
    pDay  = day;
    pHour = hour;
    pMin  = min;
}

void work::create(farmer *f, dialogBox &Box, enum jobs type, resources &Res)
{
    farmboy->busy();
    
    int l = unsigned(strlen(jobs[type]))+1;
    name = new char [l];
    strcpy_s(name, l, jobs[type]);
    switch (option)
    {
        case chop:
        {
            pDay  = 0;
            pHour = 5;
            pMin  = 0;
            char buff[] = {"Chopping wood "};
            int length = unsigned(strlen(buff));
            strcpy_s(header, length, buff);
            for (int i = length; i<y-SidePlank-3; i++)
            {
                header[i] = ' ';
            }
        }
            break;
        case adventure:
        {
            pDay  = 0;
            pHour = 5;
            pMin  = 0;
            char buff[] = {"Searching for goods "};
            int length = unsigned(strlen(buff));
            strcpy_s(header, length, buff);
            for (int i = length; i<y-SidePlank-3; i++)
            {
                header[i] = ' ';
            }
        }
            break;
            
        default:
            pDay  = 0;
            pHour = 0;
            pMin  = 0;
            break;
    }
}

int work::getOption() const
{
    return option;
}

bool work::show_progress() const
{
    return !done;
}

void work::triger()
{
    done = true;
    farmboy->free();
    
    switch (option)
    {
        case chop:
        {
            Res.addWood(150);
            Box.AddQuote("Your farmer brought home 150 wood");
            break;
        }
            
        case adventure:
        {
            srand(unsigned(time(NULL)));
            int chance = rand()%100+1;
            
            if (chance<25)
            {
                Box.AddQuote("You have found some food and some seeds");
                Res.addFood(rand()%200+100);
                Res.addSeeds(rand()%200+100);
            }
            
            else if (chance<50)
            {
                Box.AddQuote("You have found some money");
                Res.addMoney(rand()%200+100);
            }
            else
            {
                Box.AddQuote("You have found a treasure chest");
                Res.addFood(rand()%200+200);
                Res.addWood(rand()%200+200);
                Res.addSeeds(rand()%200+200);
                Res.addMoney(rand()%200+200);
            }
            break;
        }
        default:
            break;
    }
}

farmer * work::getFarmer()
{
    return farmboy;
}

void work::Del()
{
    delete [] name;
}