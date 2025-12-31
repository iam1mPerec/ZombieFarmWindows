#pragma once
#include <iostream>

enum plants
{
    potato,
    corn,
    tomato,
    carrot,
    pumpkin,
    cherry,
    numberOfPlants
};

class text_plant
{
public:
    const static char plants[numberOfPlants][20];
};
const static char plants[numberOfPlants][20] =
{
    "Potatos",
    "Corn",
    "Tomatos",
    "Carrots",
    "Pumpkins",
    "Cherry"
};