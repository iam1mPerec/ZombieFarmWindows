#pragma once

enum FieldSize
{
    Small  = 3,
    Medium = 4,
    Large  = 5,
    Huge   = 6
};

class field
{
    char ** array;
    int init_x;
    int init_y;
    int oldSize;
    int field_size;
    const int maxSize;
    char ** square;
    bool visible;

public:
    field(char**);
    void BuildFence();
    void DestroyFence();
    void ChangeFieldSize();
    void openGates();
    void closeGates();
    void nSquare();
    void showField();
    void upgrade();
    void hide();
    void reveal();
    bool checkForPlace(const int j,const int i);
    int getSize();
    int getMaxSize() const;
    char ** getSquare();
};
