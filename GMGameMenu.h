#pragma once
#include "GMMainMenu.h"
#include "ptime.h"
#include "field.h"
#include "SideMenu.h"
#include "resources.h"
#include "dialogBox.h"
#include "GoodList.h"
#include "BadList.h"
#include "ProgressMenu.h"
#include "plant.h"
#include "plants.h"
#include "work.h"
#include "building.h"
#include "events_list.h"
#include "constructions.h"
#include "Shop.h"
#include "Unit.h"
#include "Tank.h"
#include "Healer.h"
#include "Zombie.h"
#include "UpGrade.h"
#include "Party.h"
#include "Horde.h"
#include "farmerAnimation.h"
#include "Inventory.h"
#include "ItemLoader.h"
#include "GMBase.h"
#include "eControls.h"

class GMGameMenu :
    public GMBase
{
protected:
    int farmerShownAt;
	int blinkedAt;
    int SidePlank;
    int BottomPlank;
    int selectedZombie;
    int x1;
    int x2;
    int y1;
    int y2;
    item* usable;
    bool battle;
    bool animate;
    bool capture;
    bool selling;
    bool revive;
    bool NightRaid;

    events_list   list;
    field         MyField;
    SideMenu      side;
    resources     Res;
    dialogBox     Dial;
    GoodList      farmers;
    BadList       stock;
    ProgressMenu  progress;
    constructions possession;
    farmerAnimation     farmerAnimation;
    inventory     items;
    itemLoader    loader;

    Horde horde;
    UpGrade upgrade;
    party troops;

    enum plants plant;
    enum shop store;

    public:
    static ptime GlobalTime;

    GMGameMenu(bool Loading, engine* engine, char** screen);
    
    void ZombieStunnedAnimation();
    void ZombieCritAnimation();
    void ZombiePirsAnimation();
    void ZombieBuffAnimation();
    void ZombieBiteAninmation();
    void healingAnimation();
    void massHealAnimation();
    void scaterShotAnimation(const int DMG);
    
    void PopUpAnimation(int frame);
    void zombieslashedAnimation(const int dmg);
    void HumanSlashedAnimation(const int position);
    
    void drawFinalWinScreen();
    void drawFinalloseScreen();
    void drawFinalInfoScreen();
    void drawFinalPopup(char popup[29][70]);
    
    void showWaves();
    void seeder();
    void deleteWaves();
    void show();
    void showTime();
    void showSide();
    int  checkSpase();
    void showDialog();
    void mapResources();
    void functional();
    void heal();
    void stun();
    void crit();
    void pirs();
    void massHeal(const int factor);
    void massExp(const int factor);
    void equip(item* item, char* name, unit* unit, bool& exit);
    void use(item* item, char* name, unit* unit, bool& exit);
    void save();
    void load();
    void clear();
    void hide();
    void attack();
    void splash(const int dmg, const int splash);
    void drawInventory();
    void drawStats();
    void swapCards(const int y1, const int x1, const int y2, const int x2);
    void fight();
    int  allMissingHp();
    void drawUpgrade();
    void reveal();
    void addUnit();
    void drawAll();
    void drawUndead();
    void massAttack(const int Dmg);
    void whosTurn();
    void drawDescription();
    void setUndead();
    bool checkWasted()         const;
    int  humanToSlash()        const;
    int  humanToSlash_revers() const;
    void itemSelector();
    void blink(const int position, bool present);
    void zombieSelector();
    void choose(const int row, const int card);
    int  cardsInRow(const int row) const;
    int  buildingExpenses(const enum structures type);
    void Building(const enum structures);
    void mapping(int& position, const int num);
    void setPlants(enum plants p);
    void CharOut(const char ch, const int y, const int x);
    void CharOut(const int, const int, const int);
    void plantSelector();
    void selector();
    void upgradeHouse();
    void Zselector(const int position);
    void choosing2lvl(const int x2);
    void manipulator_Main(eControls controls);
    void resetVariables();
    void resetTurns();
    void traiding(const int num);
    bool isBuilding(const char* name) const;
    bool isPlant(const char* name) const;
    bool isJob(const char* name) const;
    
    void manipulator_equip(eControls controls);
    void manipulator_Plants(eControls controls);
    void manipulator_Building(eControls controls);
    void manipulator_Work(eControls controls);
    void manipulator_Exit(eControls controls);
    void manipulator_Select(eControls controls);
    void manipulator_Capture(eControls controls);
    void manipulator_Attack(eControls controls);
    void manipulator_Battle(eControls controls);
    void manipulator_lvling(eControls controls);
    void manipulator_upgrading(eControls controls);
    void manipulator_Choosing(eControls controls);
    void manipulator_firstAid(eControls controls);
    void manipulator_Shop(eControls controls);
    void manipulator_Buy(eControls controls);
    void manipulator_Sell(eControls controls);
    void manipulator_Amount(eControls controls);
    void manipulator_Abilities(eControls controls);
    void manipulator_Slashing(eControls controls);
    void manipulator_Inventory(eControls controls);
    void manipulator_Bombing(eControls controls);
    
	void showQuote(string quote) override;
	void controlSignal(eControls controls) override;
    void Update(float fElapsedTime) override;
	
    ~GMGameMenu();
};
