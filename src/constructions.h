#pragma once

enum house
{
    simple   = 4,
    roomy    = 8,
    spacious = 12,
};

enum tent
{
    noTent = 2000,
    TentS  = 10000,
    TentM  = 50000,
    TentL  = 99999
};

class constructions
{
    char** screen;
    bool road;
    bool diner;
    enum tent TentSize;
    bool barracks;
    enum house HomeSize;
    int maxHomeSize;
    int maxTentSize;
    char picHome[7][15];
    char picRoad[6][25];
    char picTent[5][12];
    char picBarrack[6][16];
    bool visible;
    
public:
    constructions(char ** screen);
    bool getRoad()      const;
    bool getBarracks()  const;
    int  getHouseSize() const;
    int getMaxHouseSize() const;
    int getTentSize() const;
    int getMaxTentSize() const;
    void buildHome();
    void buildTent();
    void buildBaracks();
    void upgradeHomeSize();
    void upgradeTentSize();
    void buildRoad();
    void hide();
    void reveal();
};