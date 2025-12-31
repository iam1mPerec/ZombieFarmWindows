#pragma once

enum structures
{
    fence,
    tunel,
    house,
    tent,
    barracks,
    numberOfBuildings
};

class text_building
{
    text_building();
public:
    const static char buildings[numberOfBuildings][21];
};
const static char buildings[numberOfBuildings][21] =
{
    "Fence",
    "Tunel",
    "House",
    "Tent",
    "Barracks"
};