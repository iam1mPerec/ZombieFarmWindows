#include "GMGameMenu.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include "str.h"
#include "ptime.h"
#include "texts_1.h"
#include "resources.h"
#include "screen.h"
#include "Time.h"
#include "Options.h"
#include "Shop.h"
#include "Abilities.h"
#include "Talents.h"

using namespace std;

ptime GMGameMenu::GlobalTime(0, 0, 0);
void GMGameMenu::show()
{
    side.clear(); // or clear only when needed
    switch (side.getMenuOption()) {
    case options::main:
        side.option_main();
        break;

    case options::planting:
        side.option_planting();
        break;

    case options::building:
        side.option_building();
        break;

    case options::working:
        side.option_working();
        break;

    case options::quiting:
        side.option_quiting();
        break;

    case options::plantSelectorStart:
        side.clearSelector();
        side.option_selecting();
        break;

    case options::plantSelectorEnd:
        // no display update?
        break;

    case options::shopping:
        showDialog();
        side.option_shop();
        break;

    case options::sell:
        side.option_sell();
        break;

    case options::buy:
        side.option_buy();
        break;

    case options::amount:
        side.option_amount();
        break;

    case options::choosing:
        side.option_swap();
        break;

    case options::battle:
        side.option_battle();
        break;

    case options::lvling:
        side.option_lvling();
        break;

    case options::upgrading:
        side.option_upgrading();
        break;

    case options::slashing:
        side.option_slashing();
        break;

    case options::attacking:
        side.option_attack();
        break;

    case options::equiping:
        side.option_equip();
        break;

    case options::sorting:
        // only functional, no display
        break;

    case options::healing:
        side.option_healing();
        break;

    case options::bombing:
        side.option_slashing(); // note: same as slashing?
        break;

    case options::firstAid:
        side.option_healing();
        break;

    case options::abilities:
        if (!battle) {
            side.option_abilities(troops.getUnit(y1, x1)->getType(),
                troops.getUnit(y1, x1)->getAbility(1),
                troops.getUnit(y1, x1)->getAbility(2),
                troops.getUnit(y1, x1)->getAbility(3),
                troops.getUnit(y1, x1)->getAbility(4),
                troops.getUnit(y1, x1)->getAbility(5));
        }
        else {
            side.option_abilities(troops.getAttacker()->getType(),
                troops.getAttacker()->getAbility(1),
                troops.getAttacker()->getAbility(2),
                troops.getAttacker()->getAbility(3),
                troops.getAttacker()->getAbility(4),
                troops.getAttacker()->getAbility(5));
        }
        break;

    default:
        // handle unknown state?
        break;
    }
}

void GMGameMenu::manipulator_Abilities(eControls controls)
{
    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        side.slider(controls);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == ability_1 && !battle)
    {
        troops.getUnit(y1, x1)->lvl_up_ability(1);
        drawAll();
        selector();
        if (!troops.getUnit(y1, x1)->unUsed())
        {
            side.setMenuOption(options::battle);
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == ability_1 && battle && troops.getAttacker()->getType() == sniper)
    {
        if (troops.getAttacker()->getAbility(1))
        {
            scaterShot(troops.getAttacker()->getAbility(1) * 50);
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == ability_2 && !battle)
    {
        troops.getUnit(y1, x1)->lvl_up_ability(2);
        drawAll();
        selector();
        if (!troops.getUnit(y1, x1)->unUsed())
        {
            side.setMenuOption(options::battle);
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == ability_3 && !battle)
    {
        troops.getUnit(y1, x1)->lvl_up_ability(3);
        drawAll();
        selector();
        if (!troops.getUnit(y1, x1)->unUsed())
        {
            side.setMenuOption(options::battle);
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == ability_3 && battle && troops.getAttacker()->getType() == healer)
    {
        if (troops.getAttacker()->getAbility(3))
        {
            heal();
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == ability_4 && !battle)
    {
        troops.getUnit(y1, x1)->lvl_up_ability(4);
        drawAll();
        selector();
        if (!troops.getUnit(y1, x1)->unUsed())
        {
            side.setMenuOption(options::battle);
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == ability_4 && battle && troops.getAttacker()->getType() == healer)
    {
        if (troops.getAttacker()->getAbility(4))
        {
            massHealAnimation();
            massHeal(troops.getAttacker()->getAbility(4) * 50);
            troops.getAttacker()->usedTurn();
            whosTurn();
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == ability_5 && !battle)
    {
        troops.getUnit(y1, x1)->lvl_up_ability(5);
        drawAll();
        selector();
        if (!troops.getUnit(y1, x1)->unUsed())
        {
            side.setMenuOption(options::battle);
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == ability_5 && battle && troops.getAttacker()->getType() == healer)
    {
        if (troops.getAttacker()->getAbility(5))
        {
            revive = true;
            heal();
            drawAll();
            drawUndead();
            choose(y2, x2);

        }
    }

    if (controls == eControls::INFO)
    {
        unit* Unit = nullptr;
        if (battle)
        {
            Unit = troops.getAttacker();
        }
        else
        {
            Unit = troops.getUnit(y1, x1);
        }

        switch (Unit->getType())
        {
        case sniper:

            switch (side.getOption())
            {
            case ability_1:
                Dial.AddQuote("This ability will dial dmg to all enemies. 50 Dmg/LVL");
                break;
            case ability_2:
                Dial.AddQuote("Every 2 lvls this ability gives 1 to stun dur");
                Dial.AddQuote("This ability gives 15% stun chanse per lvl");
                break;
            case ability_3:
                Dial.AddQuote("This ability gives 15% crit chance and 30% crit dmg per lvl");
                break;
            case ability_4:
                Dial.AddQuote("This ability gives 10% splash dmg per lvl");
                break;
            case ability_5:

                Dial.AddQuote("Every 2 lvls this ability gives 1 to number of turns");
                Dial.AddQuote("This ability improves your dmg income by 3 per lvl");
                break;

            default:
                break;
            }
            break;

        case tank:
            switch (side.getOption())
            {
            case ability_1:
                Dial.AddQuote("Every 2 lvls this ability gives 1 to stun dur");
                Dial.AddQuote("This ability gives 15% stun chance per lvl");
                break;
            case ability_2:
                Dial.AddQuote("This ability gives 15% splash dmg");
                break;
            case ability_3:
                Dial.AddQuote("This ability improves defence income by 3 per lvl");
                break;
            case ability_4:
                Dial.AddQuote("This ability improves hp income by 10 per lvl");
                break;
            case ability_5:
                Dial.AddQuote("This ability improves dmg income by 5 per lvl");
                break;

            default:
                break;
            }
            break;

        case healer:
            switch (side.getOption())
            {
            case ability_1:
                Dial.AddQuote("This ability gives 25 bleed dmg per lvl");
                break;
            case ability_2:
                Dial.AddQuote("This ability increases number of turns every 2 lvl");
                Dial.AddQuote("This ability increases priority by 1 per lvl");
                break;
            case ability_3:
                Dial.AddQuote("This ability heals ally by 100 per lvl");
                break;
            case ability_4:
                Dial.AddQuote("This ability heals all allies by 50 per lvl");
                break;
            case ability_5:
                Dial.AddQuote("with 10% of his max hp per lvl");
                Dial.AddQuote("This ability brings dead ally back to life");
                break;

            default:
                break;
            }
            break;

        default:
            break;
        }
    }

    if (((controls == eControls::SUBMIT) && side.getOption() == quiting) || (controls == eControls::QUIT))
    {
        if (!battle)
        {
            side.setMenuOption(options::battle);
        }
        else
        {
            side.setMenuOption(options::attacking);
        }
    }

    if (controls == eControls::CLEAR)
    {
        Dial.clearBox();
    }
}

void GMGameMenu::manipulator_lvling(eControls controls)
{
    bool exit = false;

    if (controls == eControls::LEFT)
    {
        if (x2 == 0)
        {
            x2 = 2;
        }
        else
        {
            x2--;
        }
    }

    if (controls == eControls::RIGHT)
    {
        if (x2 == 2)
        {
            x2 = 0;
        }
        else
        {
            x2++;
        }
    }

    if (controls == eControls::INFO)
    {
        switch (x2)
        {
        case 0:
            Dial.clearBox();
            Dial.AddQuote("Strong And Durable. This Unit is ment to protect");
            break;
        case 1:
            Dial.clearBox();
            Dial.AddQuote("This unit does a lot of damage, but better off behind a Tank");
            break;
        case 2:
            Dial.clearBox();
            Dial.AddQuote("This unit will help your troops last longer in battle");
            break;

        default:
            break;
        }
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(options::battle);
        exit = true;
        resetVariables();
    }

    if (controls == eControls::SUBMIT)
    {
        switch (x2)
        {
        case 0:
            troops.addTank(y1, x1);
            break;
        case 1:
            troops.addSniper(y1, x1);
            break;
        case 2:
            troops.addHealer(y1, x1);
            break;

        default:
            Dial.AddQuote("Error!");
        }
        resetVariables();
        side.setMenuOption(options::battle);
        exit = true;
    }
    clear();
    if (!exit)
    {
        choosing2lvl(x2);
        drawUpgrade();
    }
    else
    {
        drawAll();
    }
}
void GMGameMenu::resetTurns()
{
    troops.resetTurns();
    horde.resetTurns();
}

void GMGameMenu::manipulator_Attack(eControls controls)
{
    bool exit = false;

    if (controls == eControls::UP || controls == eControls::DOWN)
    {
        side.slider(controls);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == options::attack)
    {
        resetVariables();
        drawAll();
        drawUndead();
        zombieSelector();
        side.setMenuOption(options::slashing);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == options::skills)
    {
        if (troops.getAttacker()->getType() != title::rookie)
        {
            side.setMenuOption(options::abilities);
            exit = true;
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == options::items)
    {
        int position = troops.getAttackerPos();
        y1 = position / 4;
        x1 = position % 4;
        drawInventory();
        x2 = 5;
        itemSelector();
        side.setMenuOption(options::sorting);
        exit = true;
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == options::protect)
    {
        resetVariables();
        troops.getAttacker()->setShild();
        drawAll();
        side.setOption(0);
        whosTurn();
    }

    if (controls == eControls::CLEAR)
    {
        Dial.clearBox();
    }

    if (!exit)
    {
        selector();
    }
}

void GMGameMenu::heal()
{
    resetVariables();
    side.setMenuOption(options::healing);
    choose(y2, x2);
}

void GMGameMenu::scaterShot(const int DMG)
{
    troops.getAttacker()->usedTurn();
    massAttack(DMG);
    whosTurn();

    if (battle)
    {
        side.setMenuOption(attacking);
    }
    else
    {
        side.setMenuOption(battle);
    }

    side.setOption(0);
}

void GMGameMenu::HumanSlashedAnimation(const int position)
{
    int countDown = 6;
    int row = position / 4;
    int card = position % 4;
    troops.getUnit(position)->blincking();
    drawAll();
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 21; i++)
        {
            screen[j + BottomPlank - 20 + row * 10][1 + i + card * 22] = screen[j + BottomPlank - 20 + row * 10][2 + i + card * 22];
        }
    }

    for (int j = 0; j < 10; j++)
    {
        screen[j + BottomPlank - 20 + row * 10][22 + card * 22] = ' ';
    }

    countDown--;
    print();
    Sleep(110);
    while (countDown)
    {
        if (countDown % 2 == 0)
        {
            for (int j = 0; j < 10; j++)
            {
                for (int i = 0; i < 21; i++)
                {
                    screen[j + BottomPlank - 20 + row * 10][1 + i + card * 22] = screen[j + BottomPlank - 20 + row * 10][3 + i + card * 22];
                }
            }

            for (int j = 0; j < 10; j++)
            {
                for (int i = 0; i < 2; i++)
                {
                    screen[j + BottomPlank - 20 + row * 10][22 + i + card * 22] = ' ';
                }
            }
        }

        else if (countDown % 2 != 0)
        {
            for (int j = 0; j < 10; j++)
            {
                for (int i = 21; i > 0; i--)
                {
                    screen[j + BottomPlank - 20 + row * 10][2 + i + card * 22] = screen[j + BottomPlank - 20 + row * 10][i + card * 22];
                }
            }
            for (int j = 0; j < 10; j++)
            {
                for (int i = 0; i < 2; i++)
                {
                    screen[j + BottomPlank - 20 + row * 10][1 + i + card * 22] = ' ';
                }
            }
        }

        print();
        countDown--;
        Sleep(110);
    }

    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 22; i++)
        {
            screen[j + BottomPlank - 20 + row * 10][i + 2 + card * 22] = screen[j + BottomPlank - 20 + row * 10][3 + i + card * 22];
        }
    }

    for (int j = 0; j < 10; j++)
    {
        screen[j + BottomPlank - 20 + row * 10][23 + card * 22] = ' ';
    }

    int AttackerPos = horde.getAttackerPos();
    int dmg = horde.getUnit(AttackerPos)->getAttack();
    troops.getUnit(position)->damaged(dmg);

    if (horde.getAttacker()->getType() == ghoul || horde.getAttacker()->getType() == leaper)
    {
        ZombieBiteAninmation();
        horde.getAttacker()->damage(-(dmg * 25 + horde.getAttacker()->getLvl()) / 100);
    }

    horde.getAttacker()->usedTurn();

    clear();
    drawAll();
    drawUndead();
    troops.getUnit(position)->fine();
    drawAll();
    print();
}

void GMGameMenu::whosTurn()
{
    drawAll();
    if (horde.getHighestPriority() > troops.getHighestPriority())
    {
        if (troops.rollcall())
        {
            if (horde.getAttacker()->getBleed())
            {
                zombie* Attacker = horde.getAttacker();
                x1 = horde.getAttackerPos();
                ZombiePirsAnimation();
                horde.getAttacker()->bleedOut();
                drawUndead();
                if (horde.getAttacker() != Attacker)
                {
                    whosTurn();
                }
            }
            Zselector(horde.getAttackerPos());
            side.clear();
            showSide();
            print();
            Sleep(600);
            if (horde.getAttacker())
            {
                if (!horde.getAttacker()->getStun())
                {
                    if (horde.getAttacker()->getType() == leaper)
                    {
                        HumanSlashedAnimation(humanToSlash_revers());
                    }
                    else if (horde.getAttacker()->getType() == basher)
                    {
                        x1 = horde.getAttackerPos();
                        clear();
                        drawUndead();
                        drawAll();
                        ZombieBuffAnimation();
                        horde.getAttacker()->setAtk(-1);
                        drawUndead();
                        if (horde.getAttacker()->getAttack() <= 0)
                        {
                            horde.evolve(horde.getAttackerPos());
                            drawUndead();
                        }
                        else
                        {
                            horde.getAttacker()->usedTurn();
                        }
                    }
                    else
                    {
                        HumanSlashedAnimation(humanToSlash());
                    }
                    whosTurn();
                }
                else
                {
                    x1 = horde.getAttackerPos();
                    clear();
                    drawUndead();
                    drawAll();
                    ZombieStunnedAnimation();
                    horde.getAttacker()->stunedOut();
                    horde.getAttacker()->usedTurn();
                    whosTurn();
                }
            }
        }
        else
        {
            loseScreen();
            if (NightRaid)
            {
                Dial.AddQuote("Your vilage has been eaten up during the Night Raid");
                exit(0);
            }
            battle = false;
            horde.deleteAll();
            horde.resetWaves();
            show();
        }
    }
    else
    {
        if (troops.getAttackerPos() == -1 && horde.getAttackerPos() == -1)
        {
            resetTurns();
            selector();
        }
        else
        {
            selector();
        }
    }
}

void GMGameMenu::infoScreen()
{
    mapResources();
    showTime();
    showSide();
    print();

    int a = BottomPlank / 2 - 1;
    int b = SidePlank / 2 - 1;
    int c = BottomPlank / 2 + 5;
    int d = SidePlank / 2 + 1;

    while (d < SidePlank / 2 + 36)
    {
        for (int j = a; j < c + 1; j++)
        {
            for (int i = b; i < d + 1; i++)
            {

                if (j == a || j == c)
                {
                    screen[j][i] = '_';
                }
                else if (i == b || i == d)
                {
                    screen[j][i] = '|';
                }
                else
                {
                    screen[j][i] = ' ';
                }
            }
        }
        screen[a][b] = ' ';
        screen[a][d] = ' ';
        screen[c][b] = '|';
        screen[c][d] = '|';
        a--;
        b -= 3;
        c++;
        d += 3;
        print();
		Sleep(70);
    }

    char endScreen[29][70] =
    {
        " ___________________________________________________________________ ",
        "|                            Info                                   |",
        "|                                                                   |",
        "| Zombie's Farm Frenzy is a strategy farm frenzy based              |",
        "| horror RPG. Hope you enjoy your time here.                        |",
        "|                                                                   |",
        "|                                                                   |",
        "| Controls are:                                                     |",
        "|                                                                   |",
        "| 'W' - Up                                                          |",
        "| 'S' - Down                                                        |",
        "| 'A' - Left                                                        |",
        "| 'D' - Right                                                       |",
        "| 'F' - Enter                                                       |",
        "| 'E' - Exit/Cancel                                                 |",
        "| 'I' - Info                                                        |",
        "| 'L' - Sell an item                                                |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "| Enjoy the game and try not to get eaten by zombies                |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                 - Press any key to continue -                     |",
        "|                                                                   |",
        "|___________________________________________________________________|"

    };
    for (int j = b - 2, y = 0; y < 29; j++, y++)
    {
        for (int i = a + 6, x = 0; x < 69; i++, x++)
        {
            screen[j][i] = endScreen[y][x];
        }
    }
    print();
    hide();
    reveal();
}

void GMGameMenu::loseScreen()
{
    battle = false;
    mapResources();
    showTime();
    showSide();
    print();

    int a = BottomPlank / 2 - 1;
    int b = SidePlank / 2 - 1;
    int c = BottomPlank / 2 + 5;
    int d = SidePlank / 2 + 1;

    while (d < SidePlank / 2 + 36)
    {
        for (int j = a; j < c + 1; j++)
        {
            for (int i = b; i < d + 1; i++)
            {

                if (j == a || j == c)
                {
                    screen[j][i] = '_';
                }
                else if (i == b || i == d)
                {
                    screen[j][i] = '|';
                }
                else
                {
                    screen[j][i] = ' ';
                }
            }
        }
        screen[a][b] = ' ';
        screen[a][d] = ' ';
        screen[c][b] = '|';
        screen[c][d] = '|';
        a--;
        b -= 3;
        c++;
        d += 3;
        print();
        Sleep(70);
    }

    char endScreen[29][70] =
    {
        " ___________________________________________________________________ ",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                         You've lost                               |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|    Sad enough                                                     |",
        "|                                                                   |",
        "|    May be next time you'll be luckier                             |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                                                                   |",
        "|                 - Press any key to continue -                     |",
        "|                                                                   |",
        "|___________________________________________________________________|"

    };

    for (int j = b - 2, y = 0; y < 29; j++, y++)
    {
        for (int i = a + 6, x = 0; x < 69; i++, x++)
        {
            screen[j][i] = endScreen[y][x];
        }
    }

    Dial.AddQuote("You've lost!");
    showDialog();
    print();
    clear();
    reveal();
    troops.massRevive();
    side.setMenuOption(options::main);
}

void GMGameMenu::winScreen()
{
    battle = false;
    mapResources();
    showTime();
    showSide();
    print();

    int a = BottomPlank / 2 - 1;
    int b = SidePlank / 2 - 1;
    int c = BottomPlank / 2 + 5;
    int d = SidePlank / 2 + 1;

    while (d < SidePlank / 2 + 36)
    {
        for (int j = a; j < c + 1; j++)
        {
            for (int i = b; i < d + 1; i++)
            {

                if (j == a || j == c)
                {
                    screen[j][i] = '_';
                }
                else if (i == b || i == d)
                {
                    screen[j][i] = '|';
                }
                else
                {
                    screen[j][i] = ' ';
                }
            }
        }
        screen[a][b] = ' ';
        screen[a][d] = ' ';
        screen[c][b] = '|';
        screen[c][d] = '|';
        a--;
        b -= 3;
        c++;
        d += 3;
        print();
        Sleep(70);
    }

    char endScreen[29][70] =
    {
    " ___________________________________________________________________ ",
    "|                                                                   |",
    "|                                                                   |",
    "|                                                                   |",
    "|                      Congradulations!                             |",
    "|                         You have won the battle!                  |",
    "|                                                                   |",
    "|                                                                   |",
    "|                                                                   |",
    "|                                                                   |",
    "|         Reward:                                                   |",
    "|                                                                   |",
    "|         Money                                                     |",
    "|         Exp                                                       |",
    "|                                                                   |",
    "|         Items Found:                                              |",
    "|                                                                   |",
    "|                                                                   |",
    "|                                       _________                   |",
    "|                                      /________/\\                  |",
    "|                                     |         ||                  |",
    "|                                     |_________|/                  |",
    "|                                    /________ /|                   |",
    "|                                    |        | |                   |",
    "|                                    |________|/                    |",
    "|                                                                   |",
    "|                                                                   |",
    "|                       - Press S to skip -                         |",
    "|___________________________________________________________________|"
    };

    int Money = horde.getMoney();
    int equipTicket = 0;

    while (Money >= 50)
    {
        int random = rand() % 100 + 1;

        if (random >= 50 - GlobalTime.getDay() * 2)
        {
            equipTicket++;
        }

        Money -= 50;
    }

    Money = horde.getMoney();

    if (equipTicket)
    {
        while (equipTicket)
        {
            item* Aloc = loader.getRandomEquip();

            if (endScreen[21][10] == ' ')
            {
                int j = 0;
                for (int i = 0; i < 3; i++)
                {
                    if (endScreen[17 + j * 2][10] != ' ')
                    {
                        j++;
                    }
                    else
                    {
                        i = 3;
                    }
                };

                for (int i = 0; i < 25; i++)
                {
                    if (Aloc->getName(i))
                    {
                        endScreen[17 + j * 2][10 + i] = Aloc->getName(i);
                    }
                    else
                    {
                        i = 25;
                    }
                }
            }
            items.addItem(Aloc);
            equipTicket--;
        }
    }
    else
    {
        char none[] = "None";
        for (int i = 0; i < strlen(none); i++)
        {
            endScreen[17][10 + i] = none[i];
        }
    }

    for (int j = b - 2, y = 0; y < 29; j++, y++)
    {
        for (int i = a + 6, x = 0; x < 69; i++, x++)
        {
            screen[j][i] = endScreen[y][x];
        }
    }

    int money = Money;
    int Exp = horde.getExp();
    int exp = Exp;
    int MRate = Money / 14;
    int ERate = Exp / 14;
    bool done = false;

    if (MRate <= 2)
    {
        MRate = 3;
    }

    if (ERate <= 2)
    {
        ERate = 3;
    }

    int factor_1 = 1;
    int factor_2 = 1;
    int factor_3 = 1;
    int factor_5 = 1;
    int factor_6 = 1;

    const int x_Coin1 = 50;
    const int x_Coin2 = 51;
    const int x_Coin3 = 52;
    const int x_Coin5 = 54;
    const int x_Coin6 = 55;

    const int limit = 3;

    int y1 = 21;
    int y2 = 22;
    int y3 = 24;
    int y5 = 22;
    int y6 = 23;
    //22
    char ch1 = ' ';
    char ch2 = ' ';
    char ch3 = '_';
    char ch5 = ' ';
    char ch6 = ' ';

    while (!done)
    {
        Money -= MRate;
        if (Money <= MRate)
        {
            Res.addMoney(Money);
            horde.setMoney();
            Money = 0;
        }
        else
        {
            Res.addMoney(MRate);
        }

        Exp -= ERate;
        if (Exp <= ERate)
        {
            massExp(Exp);
            horde.setExp();
            Exp = 0;
        }
        else
        {
            massExp(ERate);
        }

        if (factor_1 < limit)
        {
            screen[y1][x_Coin1] = ch1;
            ch1 = screen[y1 + 1][x_Coin1];
            screen[y1 + 1][x_Coin1] = 'o';
            y1++;
        }
        if (y1 == 28)
        {
            screen[y1][x_Coin1] = ch1;
            ch1 = ' ';
            y1 = 23;
            factor_1++;
        }

        if (factor_2 < limit)
        {
            screen[y2][x_Coin2] = ch2;
            ch2 = screen[y2 + 1][x_Coin2];
            screen[y2 + 1][x_Coin2] = 'o';
            y2++;
        }
        if (y2 == 28)
        {
            screen[y2][x_Coin2] = ch2;
            ch2 = ' ';
            y2 = 22;
            factor_2++;
        }

        if (factor_3 < limit)
        {
            screen[y3][x_Coin3] = ch3;
            ch3 = screen[y3 + 1][x_Coin3];
            screen[y3 + 1][x_Coin3] = 'o';
            y3++;
        }

        if (y3 == 28)
        {
            screen[y3][x_Coin3] = ch3;
            ch3 = ' ';
            y3 = 22;
            factor_3++;
        }

        if (factor_5 < limit)
        {
            screen[y5][x_Coin5] = ch5;
            ch5 = screen[y5 + 1][x_Coin5];
            screen[y5 + 1][x_Coin5] = 'o';
            y5++;
        }
        if (y5 == 28)
        {
            screen[y5][x_Coin5] = ch5;
            ch5 = ' ';
            y5 = 21;
            factor_5++;
        }

        if (factor_6 < limit)
        {
            screen[y6][x_Coin6] = ch6;
            ch6 = screen[y6 + 1][x_Coin6];
            screen[y6 + 1][x_Coin6] = 'o';
            y6++;
        }
        if (y6 == 28)
        {
            screen[y6][x_Coin6] = ch6;
            ch6 = ' ';
            y6 = 23;
            factor_6++;
        }

        money = Money;
        exp = Exp;
        for (int i = 0; i < LenOfNumbers(100000); i++)
        {
            screen[b + 10][31 - i] = ' ';
        }
        for (int i = 0; i < LenOfNumbers(Money); i++)
        {
            screen[b + 10][31 - i] = (char)((int)'0') + money % 10;
            money /= 10;
        }
        for (int i = 0; i < LenOfNumbers(100000); i++)
        {
            screen[b + 11][31 - i] = ' ';
        }
        for (int i = 0; i < LenOfNumbers(Exp); i++)
        {
            screen[b + 11][31 - i] = (char)((int)'0') + exp % 10;
            exp /= 10;
        }
        mapResources();
        print();

        if (Money == 0 && Exp == 0)
        {
            done = true;
            Sleep(1000);
        }
    }

    Res.addMoney(Money);
    Money = 0;
    horde.setMoney();

    massExp(Exp);
    horde.setExp();
    Exp = 0;
    clear();
    mapResources();
    troops.drawAll();
    drawAll();
    print();
}


int  GMGameMenu::humanToSlash_revers() const
{
    if (troops.rollcall())
    {
        int row = 1;
        int card = 0;

        if (!cardsInRow(row))
        {
            row--;
        }

        srand(unsigned(time(NULL)));
        card = rand() % 4;

        while ((troops.getUnit(row, card)->IsAlive() == false) || (troops.getUnit(row, card)->getType() == untitled))
        {
            card++;
            if (card == 4)
            {
                card = 0;
            }
        }

        int position = row * 4 + card;

        return position;
    }
    else
    {
        return -1;
    }
}

int GMGameMenu::humanToSlash() const
{
    if (troops.rollcall())
    {
        int row = 0;
        int card = 0;

        if (!cardsInRow(row))
        {
            row++;
        }

        srand(unsigned(time(NULL)));
        card = rand() % 4;

        while ((troops.getUnit(row, card)->IsAlive() == false) || (troops.getUnit(row, card)->getType() == untitled))
        {
            card++;
            if (card == 4)
            {
                card = 0;
            }
        }

        int position = row * 4 + card;

        return position;
    }
    else
    {
        return -1;
    }
}

void GMGameMenu::slashedAnimation(const int dmg)
{
    int countDown = 6;

    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 11; i++)
        {
            screen[5 + j][1 + i + x1 * 11] = screen[5 + j][2 + i + x1 * 11];
        }
    }
    countDown--;
    print();
    Sleep(110);
    while (countDown)
    {
        if (countDown % 2 == 0)
        {
            for (int j = 0; j < 10; j++)
            {
                for (int i = 0; i < 10; i++)
                {
                    screen[5 + j][i + 1 + x1 * 11] = screen[5 + j][3 + i + x1 * 11];
                }
            }

            for (int j = 0; j < 10; j++)
            {
                for (int i = 0; i < 2; i++)
                {
                    screen[5 + j][11 + i + x1 * 11] = ' ';
                }
            }
        }

        else if (countDown % 2 != 0)
        {
            for (int j = 0; j < 10; j++)
            {
                for (int i = 10; i > 0; i--)
                {
                    screen[5 + j][2 + i + x1 * 11] = screen[5 + j][i + x1 * 11];
                }
            }
            for (int j = 0; j < 10; j++)
            {
                for (int i = 0; i < 2; i++)
                {
                    screen[5 + j][1 + i + x1 * 11] = ' ';
                }
            }
        }
        print();
        countDown--;
        Sleep(110);
    }

    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 11; i++)
        {
            screen[5 + j][1 + i + x1 * 11] = screen[5 + j][2 + i + x1 * 11];
        }
    }

    for (int j = 0; j < 10; j++)
    {
        screen[5 + j][12 + x1 * 11] = ' ';
    }

    horde.getUnit(x1)->damage(dmg);
    drawUndead();
}

void GMGameMenu::addUnit()
{
    if (troops.rollcall() == troops.getCount())
    {
        Dial.AddQuote("Your squad is full");
    }
    else
    {
        troops.addSolder();
    }
}

int GMGameMenu::cardsInRow(const int row) const
{
    int l = 0;
    for (int i = 0; i < 4; i++)
    {
        if ((troops.getUnit(row, i)->getType() != untitled) && (troops.getUnit(row, i)->IsAlive()))
        {
            l++;
        }
    }
    return l;
}

void GMGameMenu::fight()
{
    if (troops.rollcall() == 0)
    {
        Dial.AddQuote("Your out of units! Better get some before next attack");
    }
    hide();
    drawAll();
    resetVariables();
    side.setMenuOption(options::battle);
}

void GMGameMenu::choosing2lvl(const int x2)
{
    for (int j = 0; j < 12; j++)
    {
        for (int i = 0; i < 23; i++)
        {
            screen[14 + j][10 + i + x2 * 24] = '*';
        }
    }
}

void GMGameMenu::drawUpgrade()
{
    for (int card = 0; card < 3; card++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int i = 0; i < 21; i++)
            {
                screen[15 + j][11 + i + card * 24] = upgrade[card]->getPic(j, i);
            }
        }
    }
}

void GMGameMenu::drawAll()
{
    for (int row = 0; row < 2; row++)
    {
        for (int card = 0; card < 4; card++)
        {
            for (int j = 0; j < 10; j++)
            {
                for (int i = 0; i < 21; i++)
                {
                    if (troops.getUnit(row, card)->getType() != title::untitled)
                    {
                        screen[j + BottomPlank - 20 + row * 10][2 + i + card * 22] = troops.getUnit(row, card)->getPic(j, i);
                    }
                    else
                    {
                        screen[j + BottomPlank - 20 + row * 10][2 + i + card * 22] = ' ';
                    }
                }
            }
        }
    }
    showWaves();
}

void GMGameMenu::deleteWaves()
{
    int count = horde.getCount();

    horde.deleteWave();

    if (count <= 8)
    {
        Dial.AddQuote("Congradulations! You've won!");
        drawAll();
        horde.resetWaves();
        side.clear();
        side.setOption(0);
        side.option_battle();
        side.setMenuOption(options::battle);
        winScreen();
        NightRaid = false;
        show();
    }
    else
    {
        clear();
        drawUndead();
    }
}

bool GMGameMenu::checkWasted() const
{
    bool AllWasted = true;

    zombie* aloc = horde.getHead();
    int count = horde.getCount();
    {
        if (count > 8)
        {
            count = 8;
        }
    }

    for (int i = 0; i < count; i++)
    {
        if (aloc->getType() != zombies::wasted)
        {
            AllWasted = false;
        }
        aloc = aloc->getNext();
    }

    return AllWasted;
}

void GMGameMenu::drawInventory()
{
    clear();
    items.Check4Dead();

    char emptyPic[5][14] =
    {
        "             ",
        "  ***********",
        "  ***empty***",
        "  ***********",
        "             "
    };

    int count = 0;

    for (int row = 0; row < 3; row++)
    {
        for (int card = 0; card < 6; card++)
        {
            for (int j = 0; j < 5; j++)
            {
                for (int i = 0; i < 13; i++)
                {
                    if ((count + y2 * 18) < items.getCount())
                    {
                        int Position = row * 6 + card;
                        screen[j + BottomPlank - 15 + row * 5][4 + i + card * 14] = items.getItem(Position + y2 * 18)->getPic(j, i);
                    }
                    else
                    {
                        if (emptyPic[j][i] == '*')
                        {
                            screen[j + BottomPlank - 15 + row * 5][3 + i + card * 14] = char(6);
                        }
                        else
                        {
                            screen[j + BottomPlank - 15 + row * 5][3 + i + card * 14] = emptyPic[j][i];
                        }
                    }
                }
            }
            count++;
        }
    }

    if (troops.getUnit(y1, x1)->getHelmet())
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                screen[j + 4][i + 26] = troops.getUnit(y1, x1)->getHelmet()->getPic(j, i);
            }
        }
    }
    else
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                if (emptyPic[j][i] == '*')
                {
                    screen[j + 4][i + 25] = char(6);
                }
                else
                {
                    screen[j + 4][i + 25] = emptyPic[j][i];
                }
            }
        }
    }

    if (troops.getUnit(y1, x1)->getChest())
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                screen[j + 9][i + 26] = troops.getUnit(y1, x1)->getChest()->getPic(j, i);
            }
        }
    }
    else
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                if (emptyPic[j][i] == '*')
                {
                    screen[j + 9][i + 25] = char(6);
                }
                else
                {
                    screen[j + 9][i + 25] = emptyPic[j][i];
                }
            }
        }
    }

    if (troops.getUnit(y1, x1)->getGloves())
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                screen[j + 14][i + 26] = troops.getUnit(y1, x1)->getGloves()->getPic(j, i);
            }
        }
    }
    else
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                if (emptyPic[j][i] == '*')
                {
                    screen[j + 14][i + 25] = char(6);
                }
                else
                {
                    screen[j + 14][i + 25] = emptyPic[j][i];
                }
            }
        }
    }

    if (troops.getUnit(y1, x1)->getBoots())
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                screen[j + 14][i + 14] = troops.getUnit(y1, x1)->getBoots()->getPic(j, i);
            }
        }
    }
    else
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                if (emptyPic[j][i] == '*')
                {
                    screen[j + 14][i + 13] = char(6);
                }
                else
                {
                    screen[j + 14][i + 13] = emptyPic[j][i];
                }
            }
        }
    }

    if (troops.getUnit(y1, x1)->getWeapon())
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                screen[j + 14][i + 2] = troops.getUnit(y1, x1)->getWeapon()->getPic(j, i);
            }
        }
    }
    else
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                if (emptyPic[j][i] == '*')
                {
                    screen[j + 14][i + 1] = char(6);
                }
                else
                {
                    screen[j + 14][i + 1] = emptyPic[j][i];
                }
            }
        }
    }

    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 21; i++)
        {
            screen[j + 4][i + 2] = troops.getUnit(y1, x1)->getPic(j, i);
        }
    }
    drawDescription();
    drawStats();
    print();
}

void GMGameMenu::drawStats()
{
    unit* UNIT = troops.getUnit(y1, x1);
    item* ITEM = nullptr;
    char  TITLE[20];

    if (x2 == 0)
    {
        ITEM = UNIT->getHelmet();
    }
    else if (x2 == 1)
    {
        ITEM = UNIT->getChest();
    }
    else if (x2 == 2)
    {
        ITEM = UNIT->getWeapon();
    }
    else if (x2 == 3)
    {
        ITEM = UNIT->getBoots();
    }
    else if (x2 == 4)
    {
        ITEM = UNIT->getGloves();
    }
    else
    {
        ITEM = items.getItem(x2 - 5 + y2 * 18);
    }
    if (ITEM)
    {
        for (int i = 0; i < 20; i++)
        {
            TITLE[i] = ITEM->getTitle(i);
        }
    }

    char statScreen[12][20] = {};

    strcpy_s(statScreen[0], "Stats:");

    int stat = 0;

    strcpy_s(statScreen[2], "Hp     ");
    strcpy_s(statScreen[3], "Dmg    ");
    strcpy_s(statScreen[4], "Def    ");
    strcpy_s(statScreen[5], "Prior  ");
    strcpy_s(statScreen[6], "Turns  ");
    strcpy_s(statScreen[8], "Splash ");
    strcpy_s(statScreen[9], "Crit   ");
    strcpy_s(statScreen[10], "Stun   ");
    strcpy_s(statScreen[11], "Pirs   ");

    stat = UNIT->getMaxHp();
    int COUNT = LenOfNumbers(stat);
    for (int i = 0; i < COUNT; i++)
    {
        statScreen[2][12 - i] = (char)((int)'0') + stat % 10;
        stat /= 10;
    }

    stat = UNIT->getDamage();
    COUNT = LenOfNumbers(stat);
    for (int i = 0; i < COUNT; i++)
    {
        statScreen[3][12 - i] = (char)((int)'0') + stat % 10;
        stat /= 10;
    }

    stat = UNIT->getDef();
    COUNT = LenOfNumbers(stat);
    for (int i = 0; i < COUNT; i++)
    {
        statScreen[4][12 - i] = (char)((int)'0') + stat % 10;
        stat /= 10;
    }

    stat = UNIT->getPriority();
    COUNT = LenOfNumbers(stat);
    for (int i = 0; i < COUNT; i++)
    {
        statScreen[5][12 - i] = (char)((int)'0') + stat % 10;
        stat /= 10;
    }

    stat = UNIT->getMaxTurns();
    COUNT = LenOfNumbers(stat);
    for (int i = 0; i < COUNT; i++)
    {
        statScreen[6][12 - i] = (char)((int)'0') + stat % 10;
        stat /= 10;
    }


    stat = UNIT->getSplash();
    COUNT = LenOfNumbers(stat);
    for (int i = 0; i < COUNT; i++)
    {
        statScreen[8][12 - i] = (char)((int)'0') + stat % 10;
        stat /= 10;
    }

    stat = UNIT->getCrit();
    COUNT = LenOfNumbers(stat);
    for (int i = 0; i < COUNT; i++)
    {
        statScreen[9][12 - i] = (char)((int)'0') + stat % 10;
        stat /= 10;
    }

    stat = UNIT->getStun();
    COUNT = LenOfNumbers(stat);
    for (int i = 0; i < COUNT; i++)
    {
        statScreen[10][12 - i] = (char)((int)'0') + stat % 10;
        stat /= 10;
    }

    stat = UNIT->getPirs();
    COUNT = LenOfNumbers(stat);
    for (int i = 0; i < COUNT; i++)
    {
        statScreen[11][12 - i] = (char)((int)'0') + stat % 10;
        stat /= 10;
    }

    if (ITEM)
    {
        stat = ITEM->getHp();
        if (x2 < 5)
        {
            stat *= -1;
        }
        else
        {
            if (equals(TITLE, "Weapon"))
            {
                if (UNIT->getWeapon())
                {
                    stat -= UNIT->getWeapon()->getHp();
                }
            }
            else if (equals(TITLE, "Helmet"))
            {
                if (UNIT->getHelmet())
                {
                    stat -= UNIT->getHelmet()->getHp();
                }
            }
            else if (equals(TITLE, "Chest"))
            {
                if (UNIT->getChest())
                {
                    stat -= UNIT->getChest()->getHp();
                }
            }
            else if (equals(TITLE, "Gloves"))
            {
                if (UNIT->getGloves())
                {
                    stat -= UNIT->getGloves()->getHp();
                }
            }
            else if (equals(TITLE, "Boots"))
            {
                if (UNIT->getBoots())
                {
                    stat -= UNIT->getBoots()->getHp();
                }
            }
        }
        if (stat)
        {
            COUNT = LenOfNumbers(stat);
            if (stat > 0)
            {
                statScreen[2][14] = '+';
            }
            else
            {
                statScreen[2][14] = '-';
                stat *= -1;
            }
            for (int i = COUNT; i > 0; i--)
            {
                statScreen[2][14 + i] = (char)((int)'0') + stat % 10;
                stat /= 10;
            }
        }

        stat = ITEM->getDmg();
        if (x2 < 5)
        {
            stat *= -1;
        }
        else
        {
            if (equals(TITLE, "Weapon"))
            {
                if (UNIT->getWeapon())
                {
                    stat -= UNIT->getWeapon()->getDmg();
                }
            }
            else if (equals(TITLE, "Helmet"))
            {
                if (UNIT->getHelmet())
                {
                    stat -= UNIT->getHelmet()->getDmg();
                }
            }
            else if (equals(TITLE, "Chest"))
            {
                if (UNIT->getChest())
                {
                    stat -= UNIT->getChest()->getDmg();
                }
            }
            else if (equals(TITLE, "Gloves"))
            {
                if (UNIT->getGloves())
                {
                    stat -= UNIT->getGloves()->getDmg();
                }
            }
            else if (equals(TITLE, "Boots"))
            {
                if (UNIT->getBoots())
                {
                    stat -= UNIT->getBoots()->getDmg();
                }
            }
        }
        if (stat)
        {
            COUNT = LenOfNumbers(stat);
            if (stat > 0)
            {
                statScreen[3][14] = '+';
            }
            else
            {
                statScreen[3][14] = '-';
                stat *= -1;
            }
            for (int i = COUNT; i > 0; i--)
            {
                statScreen[3][14 + i] = (char)((int)'0') + stat % 10;
                stat /= 10;
            }
        }

        stat = ITEM->getDef();
        if (x2 < 5)
        {
            stat *= -1;
        }
        else
        {
            if (equals(TITLE, "Weapon"))
            {
                if (UNIT->getWeapon())
                {
                    stat -= UNIT->getWeapon()->getDef();
                }
            }
            else if (equals(TITLE, "Helmet"))
            {
                if (UNIT->getHelmet())
                {
                    stat -= UNIT->getHelmet()->getDef();
                }
            }
            else if (equals(TITLE, "Chest"))
            {
                if (UNIT->getChest())
                {
                    stat -= UNIT->getChest()->getDef();
                }
            }
            else if (equals(TITLE, "Gloves"))
            {
                if (UNIT->getGloves())
                {
                    stat -= UNIT->getGloves()->getDef();
                }
            }
            else if (equals(TITLE, "Boots"))
            {
                if (UNIT->getBoots())
                {
                    stat -= UNIT->getBoots()->getDef();
                }
            }
        }
        if (stat)
        {
            COUNT = LenOfNumbers(stat);
            if (stat > 0)
            {
                statScreen[4][14] = '+';
            }
            else
            {
                statScreen[4][14] = '-';
                stat *= -1;
            }
            for (int i = COUNT; i > 0; i--)
            {
                statScreen[4][14 + i] = (char)((int)'0') + stat % 10;
                stat /= 10;
            }
        }

        stat = ITEM->getPriority();
        if (x2 < 5)
        {
            stat *= -1;
        }
        else
        {
            if (equals(TITLE, "Helmet"))
            {
                if (UNIT->getHelmet())
                {
                    stat -= UNIT->getHelmet()->getPriority();
                }
            }
        }
        if (stat)
        {
            COUNT = LenOfNumbers(stat);
            if (stat > 0)
            {
                statScreen[5][14] = '+';
            }
            else
            {
                statScreen[5][14] = '-';
                stat *= -1;
            }
            for (int i = COUNT; i > 0; i--)
            {
                statScreen[5][14 + i] = (char)((int)'0') + stat % 10;
                stat /= 10;
            }
        }

        stat = ITEM->getTurns();
        if (x2 < 5)
        {
            stat *= -1;
        }
        else
        {
            if (equals(TITLE, "Weapon"))
            {
                if (UNIT->getWeapon())
                {
                    stat -= UNIT->getWeapon()->getTurns();
                }
            }
        }
        if (stat)
        {
            COUNT = LenOfNumbers(stat);
            if (stat > 0)
            {
                statScreen[6][14] = '+';
            }
            else
            {
                statScreen[6][14] = '-';
                stat *= -1;
            }
            for (int i = COUNT; i > 0; i--)
            {
                statScreen[6][14 + i] = (char)((int)'0') + stat % 10;
                stat /= 10;
            }
        }

        stat = ITEM->getSplash();
        if (x2 < 5)
        {
            stat *= -1;
        }
        else
        {
            if (equals(TITLE, "Weapon"))
            {
                if (UNIT->getWeapon())
                {
                    stat -= UNIT->getWeapon()->getSplash();
                }
            }
        }
        if (stat)
        {
            COUNT = LenOfNumbers(stat);
            if (stat > 0)
            {
                statScreen[8][14] = '+';
            }
            else
            {
                statScreen[8][14] = '-';
                stat *= -1;
            }
            for (int i = COUNT; i > 0; i--)
            {
                statScreen[8][14 + i] = (char)((int)'0') + stat % 10;
                stat /= 10;
            }
            statScreen[8][15 + COUNT] = '%';
        }

        stat = ITEM->getCrit();
        if (x2 < 5)
        {
            stat *= -1;
        }
        else
        {
            if (equals(TITLE, "Weapon"))
            {
                if (UNIT->getWeapon())
                {
                    stat -= UNIT->getWeapon()->getCrit();
                }
            }
        }
        if (stat)
        {
            COUNT = LenOfNumbers(stat);
            if (stat > 0)
            {
                statScreen[9][14] = '+';
            }
            else
            {
                statScreen[9][14] = '-';
                stat *= -1;
            }
            for (int i = COUNT; i > 0; i--)
            {
                statScreen[9][14 + i] = (char)((int)'0') + stat % 10;
                stat /= 10;
            }
            statScreen[9][15 + COUNT] = '%';
        }

        stat = ITEM->getStun();
        if (x2 < 5)
        {
            stat *= -1;
        }
        else
        {
            if (equals(TITLE, "Weapon"))
            {
                if (UNIT->getWeapon())
                {
                    stat -= UNIT->getWeapon()->getStun();
                }
            }
        }
        if (stat)
        {
            COUNT = LenOfNumbers(stat);
            if (stat > 0)
            {
                statScreen[10][14] = '+';
            }
            else
            {
                statScreen[10][14] = '-';
                stat *= -1;
            }
            for (int i = COUNT; i > 0; i--)
            {
                statScreen[10][14 + i] = (char)((int)'0') + stat % 10;
                stat /= 10;
            }
            statScreen[10][15 + COUNT] = '%';
        }

        stat = ITEM->getPirs();
        if (x2 < 5)
        {
            stat *= -1;
        }
        else
        {
            if (equals(TITLE, "Weapon"))
            {
                if (UNIT->getWeapon())
                {
                    stat -= UNIT->getWeapon()->getPirs();
                }
            }
        }
        if (stat)
        {
            COUNT = LenOfNumbers(stat);
            if (stat > 0)
            {
                statScreen[11][14] = '+';
            }
            else
            {
                statScreen[11][14] = '-';
                stat *= -1;
            }
            for (int i = COUNT; i > 0; i--)
            {
                statScreen[11][14 + i] = (char)((int)'0') + stat % 10;
                stat /= 10;
            }
        }
    }

    for (int j = 0; j < 12; j++)
    {
        for (int i = 0; i < 20; i++)
        {
            if (statScreen[j][i] != '\0')
            {
                screen[j + 5][i + 40] = statScreen[j][i];
            }
        }
    }

}

void GMGameMenu::ZombieCritAnimation()
{
    int timer = 2;
    int count = 5;
    char buff[7][9] = {};

    while (count)
    {
        while (timer)
        {
            switch (timer)
            {
            case 2:
            {
                strcpy_s(buff[0], 9, "   |    \0");
                strcpy_s(buff[1], 9, " $   /  \0");
                strcpy_s(buff[2], 9, "        \0");
                strcpy_s(buff[3], 9, "_     _ \0");
                strcpy_s(buff[4], 9, "        \0");
                strcpy_s(buff[5], 9, " /   $  \0");
                strcpy_s(buff[6], 9, "   |    \0");

                break;
            }
            case 1:
            {
                strcpy_s(buff[0], 9, "        \0");
                strcpy_s(buff[1], 9, "        \0");
                strcpy_s(buff[2], 9, "        \0");
                strcpy_s(buff[3], 9, " _$|/_  \0");
                strcpy_s(buff[4], 9, "  /|$   \0");
                strcpy_s(buff[5], 9, "        \0");
                strcpy_s(buff[6], 9, "        \0");

                break;
            }
            }

            for (int j = 0; j < 7; j++)
            {
                for (int i = 0; i < 8; i++)
                {
                    if (buff[j][i] == '$')
                    {
                        CharOut('\\', j + 7, i + 3 + x1 * 11);
                    }
                    else
                    {
                        CharOut(buff[j][i], j + 7, i + 3 + x1 * 11);
                    }
                }
            }
            timer--;
            Sleep(100);
            print();
        }
        count--;
        timer = 2;
    }
}

void GMGameMenu::ZombieStunnedAnimation()
{
    int timer = 8;
    int count = 2;
    char buff[4][9] = {};

    while (count)
    {
        while (timer)
        {
            switch (timer)
            {
            case 8:
            {
                strcpy_s(buff[0], 9, "  ____  \0");
                strcpy_s(buff[1], 9, " |  __| \0");
                strcpy_s(buff[2], 9, " |____  \0");
                strcpy_s(buff[3], 9, "        \0");

                break;
            }
            case 7:
            {
                strcpy_s(buff[0], 9, "   /$   \0");
                strcpy_s(buff[1], 9, "  /  $  \0");
                strcpy_s(buff[2], 9, "  $ $/  \0");
                strcpy_s(buff[3], 9, "   $    \0");

                break;
            }
            case 6:
            {
                strcpy_s(buff[0], 9, "  ____  \0");
                strcpy_s(buff[1], 9, " |    | \0");
                strcpy_s(buff[2], 9, " | |__| \0");
                strcpy_s(buff[3], 9, "        \0");

                break;
            }
            case 5:
            {
                strcpy_s(buff[0], 9, "  /$    \0");
                strcpy_s(buff[1], 9, " /  $   \0");
                strcpy_s(buff[2], 9, "  / /   \0");
                strcpy_s(buff[3], 9, "  $/    \0");

                break;
            }
            case 4:
            {
                strcpy_s(buff[0], 9, "  ____  \0");
                strcpy_s(buff[1], 9, "  __  | \0");
                strcpy_s(buff[2], 9, " |____| \0");
                strcpy_s(buff[3], 9, "        \0");

                break;
            }
            case 3:
            {

                strcpy_s(buff[0], 9, "    $   \0");
                strcpy_s(buff[1], 9, "  /$ $  \0");
                strcpy_s(buff[2], 9, "  $  /  \0");
                strcpy_s(buff[3], 9, "   $/   \0");

                break;
            }
            case 2:
            {
                strcpy_s(buff[0], 9, "  _     \0");
                strcpy_s(buff[1], 9, " | | |  \0");
                strcpy_s(buff[2], 9, " |___|  \0");
                strcpy_s(buff[3], 9, "        \0");

                break;
            }
            case 1:
            {
                strcpy_s(buff[0], 9, "  /$    \0");
                strcpy_s(buff[1], 9, " / /    \0");
                strcpy_s(buff[2], 9, " $  /   \0");
                strcpy_s(buff[3], 9, "  $/    \0");

                break;
            }
            }

            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 8; i++)
                {
                    if (buff[j][i] == '$')
                    {
                        CharOut('\\', j + 7, i + 3 + x1 * 11);
                    }
                    else
                    {
                        CharOut(buff[j][i], j + 7, i + 3 + x1 * 11);
                    }
                }
            }
            timer--;
            Sleep(100);
            print();
        }
        count--;
        timer = 8;
    }
    drawUndead();
}

void GMGameMenu::drawDescription()
{
    if ((x2 >= 5) && (items.getCount() > ((x2 - 5) + y2 * 18)))
    {
        for (int j = 0; j < 14; j++)
        {
            for (int i = 0; i < 28; i++)
            {
                screen[5 + j][SidePlank - 28 + i] = items.getItem((x2 - 5) + y2 * 18)->getDescript(j, i);
            }
        }
    }
    else if (x2 == 0)
    {
        if (troops.getUnit(y1, x1)->getHelmet())
        {
            for (int j = 0; j < 14; j++)
            {
                for (int i = 0; i < 28; i++)
                {
                    screen[5 + j][SidePlank - 28 + i] = troops.getUnit(y1, x1)->getHelmet()->getDescript(j, i);
                }
            }
        }
    }
    else if (x2 == 1)
    {
        if (troops.getUnit(y1, x1)->getChest())
        {
            for (int j = 0; j < 14; j++)
            {
                for (int i = 0; i < 28; i++)
                {
                    screen[5 + j][SidePlank - 28 + i] = troops.getUnit(y1, x1)->getChest()->getDescript(j, i);
                }
            }
        }
    }
    else if (x2 == 2)
    {
        if (troops.getUnit(y1, x1)->getWeapon())
        {
            for (int j = 0; j < 14; j++)
            {
                for (int i = 0; i < 28; i++)
                {
                    screen[5 + j][SidePlank - 28 + i] = troops.getUnit(y1, x1)->getWeapon()->getDescript(j, i);
                }
            }
        }
    }
    else if (x2 == 3)
    {
        if (troops.getUnit(y1, x1)->getBoots())
        {
            for (int j = 0; j < 14; j++)
            {
                for (int i = 0; i < 28; i++)
                {
                    screen[5 + j][SidePlank - 28 + i] = troops.getUnit(y1, x1)->getBoots()->getDescript(j, i);
                }
            }
        }
    }
    else if (x2 == 4)
    {
        if (troops.getUnit(y1, x1)->getGloves())
        {
            for (int j = 0; j < 14; j++)
            {
                for (int i = 0; i < 28; i++)
                {
                    screen[5 + j][SidePlank - 28 + i] = troops.getUnit(y1, x1)->getGloves()->getDescript(j, i);
                }
            }
        }
    }
}

void GMGameMenu::upgradeHouse()
{
    possession.upgradeHomeSize();
}

void GMGameMenu::functional()
{
    if (possession.getBarracks() && GlobalTime.getMin() % 8 == 0 && GlobalTime.getSec() == 0)
    {
        if (!battle)
        {
            massHeal(8);
            if (possession.getBarracks())
            {
                massExp(1);
            }
        }
    }
    if (side.getMenuOption() == options::battle)
    {
        drawAll();
    }
    if (GlobalTime.getSec() % 30 == 0)
    {
        Animation.show();
    }
    showDialog();
    showTime();
    showSide();
    mapResources();
    print();
}

void GMGameMenu::manipulator_Capture(eControls controls)
{
    if (controls == eControls::UP)
    {
        if (y2 > BottomPlank / 2 - (MyField.getSize() - 1))
        {
            y2--;
        }
    }

    if (controls == eControls::DOWN)
    {
        if (y2 < BottomPlank / 2 + (MyField.getSize() - 1))
        {
            y2++;
        }
    }

    if (controls == eControls::LEFT)
    {
        if (x2 > SidePlank / 2 - (MyField.getSize() - 1))
        {
            x2--;
        }
    }

    if (controls == eControls::RIGHT)
    {
        if (x2 < SidePlank / 2 + (MyField.getSize() - 1))
        {
            x2++;
        }
    }
    MyField.showField();
    plantSelector();

    if (controls == eControls::QUIT)
    {
        MyField.showField();
        CharOut('*', y1, x1);
        side.setMenuOption(options::plantSelectorStart);
    }

    if (controls == eControls::SUBMIT)
    {
        if (!checkSpase())
        {
            MyField.showField();
            Dial.AddQuote("You are out of space boddy");
            side.setMenuOption(planting);
        }
        else if (checkSpase() * (plant + 1) > Res.getSeeds())
        {
            Dial.AddQuote("Sorry but you are out of seeds");
        }
        else
        {
            Res.addSeeds(-checkSpase() * (plant + 1));
            mapResources();
            side.clear();
            Animation.startPlanting(x1, x2, y1, y2, plant, farmers.checkForFreeFarmer());
            print();
            side.setMenuOption(options::main);
        }
    }
}

int GMGameMenu::checkSpase()
{
    int space = 0;
    for (int j = BottomPlank / 2 - MyField.getSize() + 1, h = 0; j < BottomPlank / 2 + MyField.getSize(); j++, h++)
    {
        for (int i = SidePlank / 2 - MyField.getSize() + 1, l = 0; i < SidePlank / 2 + MyField.getSize(); i++, l++)
        {
            if (MyField.checkForPlace(h, l) && screen[j][i] == '*')
            {
                space++;
            }
        }
    }
    return space;
}

void GMGameMenu::plantSelector()
{
    int l1 = x1;
    int l2 = x2;
    int h1 = y1;
    int h2 = y2;

    if (l1 > l2)
    {
        l1 = x2;
        l2 = x1;
    }
    if (h1 > h2)
    {
        h1 = y2;
        h2 = y1;
    }

    for (int j = h1; j < h2 + 1; j++)
    {
        for (int i = l1; i < l2 + 1; i++)
        {
            CharOut('*', j, i);
        }
    }

}

void GMGameMenu::manipulator_Select(eControls controls)
{
    MyField.showField();
    print();

    if (controls == eControls::UP)
    {
        if (y1 > BottomPlank / 2 - (MyField.getSize() - 1))
        {
            --y1;
        }
        CharOut('*', y1, x1);
    }

    if (controls == eControls::DOWN)
    {
        if (y1 < BottomPlank / 2 + (MyField.getSize() - 1))
        {
            ++y1;
        }
        CharOut('*', y1, x1);
    }

    if (controls == eControls::LEFT)
    {
        if (x1 > SidePlank / 2 - (MyField.getSize() - 1))
        {
            --x1;
        }
        CharOut('*', y1, x1);
    }

    if (controls == eControls::RIGHT)
    {
        if (x1 < SidePlank / 2 + (MyField.getSize() - 1))
        {
            ++x1;
        }
        CharOut('*', y1, x1);
    }

    if (controls == eControls::SUBMIT)
    {
        x2 = x1;
        y2 = y1;
        plantSelector();
        side.setMenuOption(options::plantSelectorEnd);
    }

    if (controls == eControls::QUIT)
    {
        MyField.showField();
        side.setMenuOption(options::planting);
    }
}

void GMGameMenu::manipulator_Main(eControls controls)
{
    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        side.slider(controls);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == options::grow)
    {
        if (Animation.getDone() != chill)
        {
            Dial.AddQuote("You are already working on the field");
        }
        else
        {
            side.setMenuOption(options::planting);
        }
    }
    if ((controls == eControls::SUBMIT) && side.getOption() == options::construct)
    {
        side.setMenuOption(options::building);
    }
    if ((controls == eControls::SUBMIT) && side.getOption() == options::activity)
    {
        side.setMenuOption(options::working);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == options::units)
    {
        fight();
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == options::save)
    {
        save();
        Dial.AddQuote("The game is saved");
        showDialog();
    }

    if (((controls == eControls::SUBMIT) && side.getOption() == 5) || (controls == eControls::QUIT))
    {
        Dial.AddQuote("Sure you want to quit?");
        side.setMenuOption(options::quiting);
    }

    if (controls == eControls::CLEAR)
    {
        Dial.clearBox();
    }
}

void GMGameMenu::manipulator_Plants(eControls controls)
{
    int g;
    g = getchar();

    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        side.slider(controls);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == potato)
    {
        if (!farmers.checkForFreeFarmer())
        {
            Dial.AddQuote("Sorry boddy, but you are out of farmers!");
        }
        else
        {
            plant = plants::potato;
            y1 = BottomPlank / 2 - (MyField.getSize() - 1);
            x1 = SidePlank / 2 - (MyField.getSize() - 1);
            CharOut('*', y1, x1);
            side.setMenuOption(options::plantSelectorStart);
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == corn)
    {
        if (!farmers.checkForFreeFarmer())
        {
            Dial.AddQuote("Sorry boddy, but you are out of farmers!");
        }
        else
        {
            plant = corn;
            y1 = BottomPlank / 2 - (MyField.getSize() - 1);
            x1 = SidePlank / 2 - (MyField.getSize() - 1);
            CharOut('*', y1, x1);
            side.setMenuOption(options::plantSelectorStart);
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == tomato)
    {
        if (!farmers.checkForFreeFarmer())
        {
            Dial.AddQuote("Sorry boddy, but you are out of farmers!");
        }
        else
        {
            plant = tomato;
            y1 = BottomPlank / 2 - (MyField.getSize() - 1);
            x1 = SidePlank / 2 - (MyField.getSize() - 1);
            CharOut('*', y1, x1);
            side.setMenuOption(options::plantSelectorStart);
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == carrot)
    {
        if (!farmers.checkForFreeFarmer())
        {
            Dial.AddQuote("Sorry boddy, but you are out of farmers!");
        }
        else
        {
            plant = carrot;
            y1 = BottomPlank / 2 - (MyField.getSize() - 1);
            x1 = SidePlank / 2 - (MyField.getSize() - 1);
            CharOut('*', y1, x1);
            side.setMenuOption(options::plantSelectorStart);
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == pumpkin)
    {
        if (!farmers.checkForFreeFarmer())
        {
            Dial.AddQuote("Sorry boddy, but you are out of farmers!");
        }
        else
        {
            plant = pumpkin;
            y1 = BottomPlank / 2 - (MyField.getSize() - 1);
            x1 = SidePlank / 2 - (MyField.getSize() - 1);
            CharOut('*', y1, x1);
            side.setMenuOption(options::plantSelectorStart);
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == cherry)
    {
        if (!farmers.checkForFreeFarmer())
        {
            Dial.AddQuote("Sorry boddy, but you are out of farmers!");
        }
        else
        {
            plant = cherry;
            y1 = BottomPlank / 2 - (MyField.getSize() - 1);
            x1 = SidePlank / 2 - (MyField.getSize() - 1);
            CharOut('*', y1, x1);
            side.setMenuOption(options::plantSelectorStart);
        }
    }

    if (controls == eControls::CLEAR)
    {
        Dial.clearBox();
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(options::main);
    }
}

void GMGameMenu::Building(const enum structures building)
{
    bool maxed = false;

    if (building == numberOfBuildings)
    {
        Dial.AddQuote("Error Wrong input!");
    }
    else
    {
        if (list.check4(buildings[building]))
        {
            Dial.AddQuote("You are building that already!");
            showDialog();
        }
        else
        {
            switch (building)
            {
            case fence:
                if (MyField.getSize() == MyField.getMaxSize())
                {
                    maxed = true;
                }
                break;

            case tunel:
                if (possession.getRoad())
                {
                    maxed = true;
                }
                break;

            case house:
                if (possession.getHouseSize() == possession.getMaxHouseSize())
                {
                    maxed = true;
                }
                break;

            case tent:
                if (possession.getTentSize() == possession.getMaxTentSize())
                {
                    maxed = true;
                }
                break;

            case barracks:
                if (possession.getBarracks())
                {
                    maxed = true;
                }
                break;

            default:
                break;
            }
            if (maxed)
            {
                Dial.AddQuote("You have maxed that already");
                showDialog();
            }
            else
            {
                if (!farmers.checkForFreeFarmer())
                {
                    Dial.AddQuote("Sorry boddy, but you are out of farmers!");
                    showDialog();
                }
                else
                {
                    if (buildingExpenses(building) > Res.getWood())
                    {
                        Dial.AddQuote("You do not have enough resources!");
                        showDialog();
                    }
                    else
                    {
                        Res.addWood(-buildingExpenses(building));
                        list.AddBuilding(MyField, farmers.checkForFreeFarmer(), Dial, building, possession, screen);
                    }
                }
            }
        }
    }

}

void GMGameMenu::manipulator_Building(eControls controls)
{
    reveal();
    side.clear();

    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        side.slider(controls);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == fence)
    {
        Building(fence);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == tunel)
    {
        Building(tunel);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == house)
    {
        Building(house);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == tent)
    {
        Building(tent);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == barracks)
    {
        Building(barracks);
    }


    if ((controls == eControls::INFO) && side.getOption() == fence)
    {
        Dial.AddQuote("Large one will cost you 1000 wood");
        Dial.AddQuote("Medium one will cost you 500 wood");
        Dial.AddQuote("Small one will cost you 250 wood");
        Dial.AddQuote("Larger fence will alow you to plant more");
    }

    if ((controls == eControls::INFO) && side.getOption() == tunel)
    {
        Dial.AddQuote("Will cost you 200 wood to build one");
        Dial.AddQuote("To trade with survivers or even hire them");
        Dial.AddQuote("Tunel will alow you to travel to UnderTown");
    }

    if ((controls == eControls::INFO) && side.getOption() == house)
    {
        Dial.AddQuote("Spacious can hold 8 and costs 500 wood");
        Dial.AddQuote("Large can hold 8 and costs 250 wood");
        Dial.AddQuote("Small house can only hold up to 4 farmers");
    }

    if ((controls == eControls::INFO) && side.getOption() == tent)
    {
        Dial.AddQuote("Large one alows to store 99999 and will cost 1000 wood");
        Dial.AddQuote("Medium tent alows to store 50000 and will cost 500 wood");
        Dial.AddQuote("Small tent alows to store 10000 and will cost 250 wood");
        Dial.AddQuote("Without one you can only stor 2000 each");
        Dial.AddQuote("LArger tent will alow you to store more resources");
    }

    if ((controls == eControls::INFO) && side.getOption() == barracks)
    {
        Dial.AddQuote("Costs 1500 to build, but definitely worth it");
        Dial.AddQuote("Is a place for your units to train and heal");
    }

    if (controls == eControls::CLEAR)
    {
        Dial.clearBox();
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(options::main);
    }

}

int GMGameMenu::buildingExpenses(const enum structures type)
{
    int cost = 0;
    switch (type)
    {
    case fence:
    {
        switch (MyField.getSize())
        {
        case Small:
            cost = 250;
            break;
        case Medium:
            cost = 500;
            break;
        case Large:
            cost = 1000;
        default:
            cost = 0;
            break;
        }
        break;
    }

    case tunel:
    {
        cost = 200;
        break;
    }

    case barracks:
    {
        cost = 1500;
        break;
    }

    case house:
    {
        switch (possession.getHouseSize())
        {
        case simple:
            cost = 500;
            break;
        case roomy:
            cost = 1000;
            break;
        case spacious:
            cost = 1500;
            break;
        default:
            cost = 0;
            break;
        }
    }
    case tent:
    {
        switch (possession.getTentSize())
        {
        case noTent:
            cost = 250;
            break;
        case TentS:
            cost = 500;
            break;
        case TentM:
            cost = 1000;
        default:
            cost = 0;
            break;
        }
    }
    default:
        break;
    }
    return cost;
}

void GMGameMenu::manipulator_Shop(eControls controls)
{
    side.clear();

    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        side.slider(controls);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == shop::buying)
    {
        selling = false;
        Dial.AddQuote("So you are willing to buy something?");
        showDialog();
        side.setMenuOption(options::buy);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == shop::selling)
    {
        selling = true;
        Dial.AddQuote("So you are willing to sell something?");
        showDialog();
        side.setMenuOption(options::sell);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == shop::farmers)
    {
        if (possession.getHouseSize() <= farmers.getcount())
        {
            Dial.AddQuote("You do not have enough space at home!");
        }
        else
        {
            if (Res.getMoney() < 200)
            {
                Dial.AddQuote("Sorry but you dont have enoug money");
            }
            else
            {
                Res.addMoney(-200);
                mapResources();
                farmers.hire();
            }
        }
    }

    if (controls == eControls::CLEAR)
    {
        Dial.clearBox();
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(options::main);
    }
}

void GMGameMenu::manipulator_Sell(eControls controls)
{
    side.clear();

    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        side.slider(controls);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == shop::wood)
    {
        store = wood;
        side.setMenuOption(options::amount);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == shop::seeds)
    {
        store = seeds;
        side.setMenuOption(options::amount);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == shop::food)
    {
        store = food;
        side.setMenuOption(options::amount);
    }

    if (controls == eControls::CLEAR)
    {
        Dial.clearBox();
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(8);
    }
}

void GMGameMenu::manipulator_Buy(eControls controls)
{
    side.clear();

    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        side.slider(controls);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == shop::wood)
    {
        store = wood;
        side.setMenuOption(options::amount);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == shop::seeds)
    {
        store = seeds;
        side.setMenuOption(options::amount);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == shop::food)
    {
        store = food;
        side.setMenuOption(options::amount);
    }

    if (controls == eControls::CLEAR)
    {
        Dial.clearBox();
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(8);
    }
}

void GMGameMenu::traiding(const int num)
{
    if (selling)
    {
        switch (store)
        {
        case wood:
        {
            if (Res.getWood() >= num)
            {
                Res.addWood(-num);
                Res.addMoney(num);
            }
            else
            {
                Dial.AddQuote("You dont have enough wood");
            }
        }
        break;

        case seeds:
        {
            if (Res.getSeeds() >= num)
            {
                Res.addSeeds(-num);
                Res.addMoney(num / 4);
            }
            else
            {
                Dial.AddQuote("You dont have enough seeds");
            }
        }
        break;


        case food:
        {
            if (Res.getFood() >= num)
            {
                Res.addFood(-num);
                Res.addMoney(num / 2);
            }
            else
            {
                Dial.AddQuote("You dont have enough food");
            }
        }
        break;

        default:
            break;
        }
    }
    else
    {
        switch (store)
        {
        case wood:
        {
            if (Res.getMoney() < num * 2)
            {
                Dial.AddQuote("You dont have enough money!");
            }
            else
            {
                Res.addMoney(-num * 2);
                Res.addWood(num);
            }
        }
        break;

        case seeds:
        {
            if (Res.getMoney() < num / 2)
            {
                Dial.AddQuote("You dont have enough money!");
            }
            else
            {
                Res.addMoney(-num / 2);
                Res.addSeeds(num);
            }
        }
        break;

        case food:
        {
            if (Res.getMoney() < num)
            {
                Dial.AddQuote("You dont have enough money!");
            }
            else
            {
                Res.addMoney(-num);
                Res.addFood(num);
            }
        }
        break;

        default:
            break;
        }
    }
}

void GMGameMenu::manipulator_Amount(eControls controls)
{
    side.clear();

    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        side.slider(controls);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == 0)
    {
        traiding(100);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == 1)
    {
        traiding(250);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == 2)
    {
        traiding(500);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == 3)
    {
        traiding(1000);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == 4)
    {
        traiding(5000);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == 5)
    {
        traiding(10000);
    }

    if (controls == eControls::CLEAR)
    {
        Dial.clearBox();
    }

    if (controls == eControls::QUIT)
    {
        if (selling)
        {
            side.setMenuOption(options::sell);
        }
        else
        {
            side.setMenuOption(options::buy);
        }
    }

}

void GMGameMenu::selector()
{
    if (troops.getAttackerPos() != -1)
    {
        troops.getAttacker()->resetShild();
        drawAll();
        int row = 0;
        int card = 0;
        if (battle)
        {
            row = troops.getAttackerPos() / 4;
            card = troops.getAttackerPos() % 4;
        }
        else
        {
            row = y1;
            card = x1;
        }

        char selector[10][22] =
        {
            "#$#$#$#$#$#$#$#$#$#$#",
            "#                   #",
            "#                   #",
            "#                   #",
            "#                   #",
            "#                   #",
            "#                   #",
            "#                   #",
            "#                   #",
            "#$#$#$#$#$#$#$#$#$#$#"
        };
        if (row < 2 && card < 4)
        {
            for (int j = 0; j < 10; j++)
            {
                for (int i = 0; i < 21; i++)
                {
                    if (selector[j][i] == '#')
                    {
                        screen[j + BottomPlank - 20 + row * 10][2 + i + card * 22] = '^';
                    }
                    else if (selector[j][i] == '$')
                    {
                        screen[j + BottomPlank - 20 + row * 10][2 + i + card * 22] = ' ';
                    }
                }
            }
        }
    }
}

void GMGameMenu::choose(int row, int card)
{
    char selector[10][22] =
    {
        "# # # # # # # # # # #",
        "#********/$*********#",
        "#*******/  $********#",
        "#******/ /$ $*******#",
        "#*****/ /  $ $******#",
        "#*****$ $ $ $ $*****#",
        "#******$ $ $/ /*****#",
        "#*******$ $  /******#",
        "#********$ $/*******#",
        "# # # # # # # # # # #"
    };
    if (row < 2 && card < 4)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int i = 0; i < 21; i++)
            {
                if (selector[j][i] == '#')
                {
                    screen[j + BottomPlank - 20 + row * 10][2 + i + card * 22] = char(6);
                }
                else if (selector[j][i] == '*')
                {
                    screen[j + BottomPlank - 20 + row * 10][2 + i + card * 22] = '^';
                }
                else if (selector[j][i] == '$')
                {
                    screen[j + BottomPlank - 20 + row * 10][2 + i + card * 22] = '\\';
                }
                else
                {
                    screen[j + BottomPlank - 20 + row * 10][2 + i + card * 22] = selector[j][i];
                }
            }
        }
    }
}

void GMGameMenu::Zselector(const int position)
{
    char selector[10][12] =
    {
        "#$#$#$#$#$#",
        "#$        #",
        "#$        #",
        "#$        #",
        "#$        #",
        "#$        #",
        "#$        #",
        "#$        #",
        "#$        #",
        "#$#$#$#$#$#"
    };

    if (position<8 && position>(-1))
    {
        for (int j = 0; j < 10; j++)
        {
            for (int i = 0; i < 11; i++)
            {
                if (selector[j][i] == '#')
                {
                    screen[5 + j][1 + i + position * 11] = char(6);
                }
                else if (selector[j][i] == '$')
                {
                    screen[5 + j][1 + i + position * 11] = ' ';
                }
            }
        }
    }
}

void GMGameMenu::manipulator_Inventory(eControls controls)
{
    bool exit = false;

    if (controls == eControls::UP)
    {
        if (x2 > 10)
        {
            x2 -= 6;
        }
        else if (x2 == 1)
        {
            x2 -= 1;
        }
        else if (x2 > 1 && x2 < 5)
        {
            x2 = 1;
        }
        else if (x2 > 4 && x2 < 11)
        {
            x2 = 4;
        }
        else
        {
            x2 = 22;
        }
    }

    if (controls == eControls::DOWN)
    {
        if (x2 == 0)
        {
            x2 = 1;
        }
        else if (x2 == 1)
        {
            x2 = 4;
        }
        else if (x2 > 1 && x2 < 5)
        {
            x2 = 5;
        }
        else if (x2 > 16)
        {
            x2 = 0;
        }
        else
        {
            x2 += 6;
        }
    }
    if (controls == eControls::LEFT)
    {
        if (x2 == 5 || x2 == 11 || x2 == 17)
        {
            x2 += 5;

            if (y2 == 0)
            {
                y2 = items.getNumberOfPages();
            }
            else
            {
                y2--;
            }
        }
        else if (x2 == 0 || x2 == 1)
        {
            x2 = 2;
        }
        else if (x2 == 2)
        {
            x2 = 4;
        }
        else
        {
            x2--;
        }
    }

    if (controls == eControls::RIGHT)
    {
        if (x2 == 10 || x2 == 16 || x2 == 22)
        {
            x2 -= 5;
            if (y2 == items.getNumberOfPages())
            {
                y2 = 0;
            }
            else
            {
                y2++;
            }
        }
        else if (x2 == 0 || x2 == 1)
        {
            x2 = 2;
        }
        else if (x2 == 4)
        {
            x2 = 2;
        }
        else
        {
            x2++;
        }
    }

    if (controls == eControls::QUIT)
    {
        if (!battle)
        {
            side.setMenuOption(options::battle);
        }
        else
        {
            side.setMenuOption(options::attacking);
        }
        exit = true;
    }

    if (controls == eControls::SELL)
    {
        if (x2 > 4)
        {
            if (items.getItem((x2 - 5) + y2 * 18))
            {
                Res.addMoney(items.getItem((x2 - 5) + y2 * 18)->getPrice());
                items.removeItem(x2 - 5 + y2 * 18);
            }
        }
        else if (x2 == 0)
        {
            if (troops.getUnit(y1, x1)->getHelmet())
            {
                items.addItem(troops.getUnit(y1, x1)->equipHelmet(nullptr));
                Res.addMoney(items.getItem(items.getCount() - 1)->getPrice());
                items.removeItem(items.getCount() - 1);
            }
        }
        else if (x2 == 1)
        {
            if (troops.getUnit(y1, x1)->getChest())
            {
                items.addItem(troops.getUnit(y1, x1)->equipChest(nullptr));
                Res.addMoney(items.getItem(items.getCount() - 1)->getPrice());
                items.removeItem(items.getCount() - 1);
            }
        }
        else if (x2 == 2)
        {
            if (troops.getUnit(y1, x1)->getWeapon())
            {
                items.addItem(troops.getUnit(y1, x1)->equipWeapon(nullptr));
                Res.addMoney(items.getItem(items.getCount() - 1)->getPrice());
                items.removeItem(items.getCount() - 1);
            }
        }
        else if (x2 == 3)
        {
            if (troops.getUnit(y1, x1)->getBoots())
            {
                items.addItem(troops.getUnit(y1, x1)->equipBoots(nullptr));
                Res.addMoney(items.getItem(items.getCount() - 1)->getPrice());
                items.removeItem(items.getCount() - 1);
            }
        }
        else if (x2 == 4)
        {
            if (troops.getUnit(y1, x1)->getGloves())
            {
                items.addItem(troops.getUnit(y1, x1)->equipGloves(nullptr));
                Res.addMoney(items.getItem(items.getCount() - 1)->getPrice());
                items.removeItem(items.getCount() - 1);
            }
        }
    }

    if (controls == eControls::SUBMIT)
    {
        if (x2 > 4)
        {
            if (items.getItem((x2 - 5) + y2 * 18))
            {
                unit* Unit = troops.getUnit(y1, x1);
                item* Item = items.getItem(x2 - 5 + y2 * 18);
                char buff[20] = {};
                char dbuff[12] = {};
                for (int i = 0; i < 20; i++)
                {
                    buff[i] = Item->getName(i);
                }
                for (int i = 0; i < 12; i++)
                {
                    if (Item->getPic(1, i + 1) != ' ')
                    {
                        dbuff[i] = Item->getPic(1, i + 1);
                    }
                    else
                    {
                        break;
                    }
                }
                switch (Item->getType())
                {
                case equipment:
                    equip(Item, dbuff, Unit, exit);
                    break;
                case consumables:
                    use(Item, dbuff, Unit, exit);
                    break;
                default:
                    break;
                }
            }
        }
        else if (x2 == 0)
        {
            if (troops.getUnit(y1, x1)->getHelmet())
            {
                items.addItem(troops.getUnit(y1, x1)->equipHelmet(nullptr));
            }
        }
        else if (x2 == 1)
        {
            if (troops.getUnit(y1, x1)->getChest())
            {
                items.addItem(troops.getUnit(y1, x1)->equipChest(nullptr));
            }
        }
        else if (x2 == 2)
        {
            if (troops.getUnit(y1, x1)->getWeapon())
            {
                items.addItem(troops.getUnit(y1, x1)->equipWeapon(nullptr));
            }
        }
        else if (x2 == 3)
        {
            if (troops.getUnit(y1, x1)->getBoots())
            {
                items.addItem(troops.getUnit(y1, x1)->equipBoots(nullptr));
            }
        }
        else if (x2 == 4)
        {
            if (troops.getUnit(y1, x1)->getGloves())
            {
                items.addItem(troops.getUnit(y1, x1)->equipGloves(nullptr));
            }
        }
    }

    if (y2 > items.getNumberOfPages())
    {
        y2 = items.getNumberOfPages();
    }

    if (!exit)
    {
        drawInventory();
        itemSelector();
    }
    else if (exit && battle)
    {
        clear();
        drawAll();
        drawUndead();
        whosTurn();
    }
    else
    {
        clear();
    }
}

void GMGameMenu::equip(item* item, char* name, unit* unit, bool& exit)
{
    if (!item->getRestriction() || unit->getType() == item->getRestriction())
    {
        if (equals(name, "Helmet"))
        {
            items.replaceItem(unit->equipHelmet(static_cast<helmet*>(item)), (x2 - 5 + y2 * 18));
        }
        if (equals(name, "Chest"))
        {
            items.replaceItem(unit->equipChest(static_cast<chest*>(item)), (x2 - 5 + y2 * 18));
        }
        if (equals(name, "Gloves"))
        {
            items.replaceItem(unit->equipGloves(static_cast<gloves*>(item)), (x2 - 5 + y2 * 18));
        }
        if (equals(name, "Boots"))
        {
            items.replaceItem(unit->equipBoots(static_cast<boots*>(item)), (x2 - 5 + y2 * 18));
        }
        if (equals(name, "Weapon"))
        {
            items.replaceItem(unit->equipWeapon(static_cast<weapon*>(item)), (x2 - 5 + y2 * 18));
        }
        if (battle)
        {
            unit->usedTurn();
            side.setMenuOption(attacking);
            exit = true;
        }
    }
    else
    {
        Dial.AddQuote("This item can not be used by your class");
    }
}

void GMGameMenu::use(item* item, char* name, unit* unit, bool& exit)
{
    if (battle)
    {
        if (equals(name, "Potion"))
        {
            if (unit->IsDamaged())
            {
                side.setMenuOption(attacking);
                unit->usedTurn();
                exit = true;
                clear();
                drawAll();
                drawUndead();
                healingAnimation();
                unit->HpUp(item->getProperty());
                item->consume();
                whosTurn();
            }
            else
            {
                Dial.AddQuote("This unit is in good health");
            }
        }
        if (equals(name, "Grenade"))
        {
            side.setMenuOption(attacking);
            unit->usedTurn();
            exit = true;
            clear();
            drawAll();
            drawUndead();
            item->consume();
            scaterShot(item->getProperty());
        }
        if (equals(name, "Kit"))
        {
            if (!troops.allHealed())
            {
                side.setMenuOption(attacking);
                unit->usedTurn();
                exit = true;
                clear();
                drawAll();
                drawUndead();
                massHealAnimation();
                massHeal(item->getProperty());
                item->consume();
                whosTurn();
            }
            else
            {
                Dial.AddQuote("There is no one to heal");
            }
        }
        if (equals(name, "Bomb"))
        {
            usable = item;
            side.setMenuOption(bombing);
            clear();
            drawAll();
            drawUndead();
            selector();
            zombieSelector();
            show();
        }
        if (equals(name, "Revive"))
        {
            resetVariables();
            revive = true;
            usable = item;
            side.setMenuOption(firstAid);
            clear();
            drawAll();
            drawUndead();
            choose(x1, y1);
            print();
            show();
        }
        if (equals(name, "Bandages"))
        {
            resetVariables();
            usable = item;
            revive = false;
            side.setMenuOption(firstAid);
            clear();
            drawAll();
            drawUndead();
            choose(x1, y1);
            print();
            show();
        }
    }
    else
    {
        if (equals(name, "Potion"))
        {
            if (unit->IsDamaged())
            {
                unit->HpUp(item->getProperty());
                item->consume();
            }
            else
            {
                Dial.AddQuote("This unit is in good health");
            }
        }
        if (equals(name, "Grenade"))
        {
            Dial.AddQuote("You can not use explosives out of combat!");
        }
        if (equals(name, "Kit"))
        {
            if (!troops.allHealed())
            {
                massHeal(item->getProperty());
                item->consume();
            }
            else
            {
                Dial.AddQuote("There is no one to heal");
            }
        }
        if (equals(name, "Bomb"))
        {
            Dial.AddQuote("You can not use explosives out of combat!");
        }
        if (equals(name, "Revive"))
        {
            if (unit->IsAlive())
            {
                Dial.AddQuote("You can not bring to live someone who's not dead");
            }
            else
            {
                unit->revive();
                unit->HpUp(item->getProperty() - 10);
                item->consume();
            }
        }
        if (equals(name, "Bandages"))
        {
            if (unit->IsDamaged())
            {
                unit->HpUp(item->getProperty());
                item->consume();
            }
            else
            {
                Dial.AddQuote("This unit is in good health");
            }
        }
    }
}

void GMGameMenu::itemSelector()
{
    int position = x2;

    char selector[5][14] =
    {
        "$$$$$$$$$$$$$",
        "$           $",
        "$           $",
        "$           $",
        "$$$$$$$$$$$$$"
    };

    if (position >= 5)
    {
        int row = (position - 5) / 6;
        int card = (position - 5) % 6;

        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                if (selector[j][i] == '$')
                {
                    screen[j + BottomPlank - 15 + row * 5][4 + i + card * 14] = char(8);
                }
                else
                {

                }
            }
        }
    }
    else if (position == 0)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                if (selector[j][i] == '$')
                {
                    screen[j + 4][i + 26] = char(8);
                }
                else
                {

                }
            }
        }
    }
    else if (position == 1)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                if (selector[j][i] == '$')
                {
                    screen[j + 9][i + 26] = char(8);
                }
                else
                {

                }
            }
        }
    }
    else if (position == 3)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                if (selector[j][i] == '$')
                {
                    screen[j + 14][i + 14] = char(8);
                }
                else
                {

                }
            }
        }
    }
    else if (position == 4)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                if (selector[j][i] == '$')
                {
                    screen[j + 14][i + 26] = char(8);
                }
                else
                {

                }
            }
        }
    }
    else
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                if (selector[j][i] == '$')
                {
                    screen[j + 14][i + 2] = char(8);
                }
                else
                {

                }
            }
        }
    }
}

void GMGameMenu::zombieSelector()
{
    int last = horde.getCount() - 1;

    if (horde.getCount() > 7)
    {
        last = 7;
    }

    while (horde.getUnit(x1)->getType() == wasted)
    {
        x1++;
        if (x1 > last)
        {
            x1 = 0;
        }
    }

    char selector[10][11] =
    {
        "# # # #  #",
        "# $****/ #",
        "#$ $**/ /#",
        "#*$ $/ /*#",
        "#**$  /**#",
        "#**/  $**#",
        "#*/ /$ $*#",
        "#/ /**$ $#",
        "# /****$ #",
        "#  # # # #"
    };
    if (x1<8 && x1>(-1))
    {
        for (int j = 0; j < 10; j++)
        {
            for (int i = 0; i < 10; i++)
            {
                if (selector[j][i] == '#')
                {
                    screen[5 + j][2 + i + x1 * 11] = char(6);
                }
                else if (selector[j][i] == '*')
                {
                    screen[5 + j][2 + i + x1 * 11] = '^';
                }
                else if (selector[j][i] == '$')
                {
                    screen[5 + j][2 + i + x1 * 11] = '\\';
                }
                else
                {
                    screen[5 + j][2 + i + x1 * 11] = selector[j][i];
                }
            }
        }
    }
}

void GMGameMenu::swapCards(const int y1, const int x1, const int y2, const int x2)
{
    troops.swap(y1, x1, y2, x2);
}

void GMGameMenu::manipulator_upgrading(eControls controls)
{
    bool exit = false;
    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        if (y1 != 1)
        {
            y1 = 1;
        }
        else
            y1 = 0;
    }

    if (controls == eControls::LEFT)
    {
        if (x1 > 0)
        {
            x1--;
        }
        else
        {
            x1 = 3;
        }
    }

    if (controls == eControls::RIGHT)
    {
        if (x1 < 3)
        {
            x1++;
        }
        else
        {
            x1 = 0;
        }
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(options::battle);
        exit = true;
    }

    if (controls == eControls::SUBMIT)
    {
        if (troops.getUnit(y1, x1)->getType() == rookie && troops.getUnit(y1, x1)->getLvl() >= 10)
        {
            clear();
            side.setMenuOption(options::lvling);
            exit = true;
            choosing2lvl(0);
            drawUpgrade();
            Dial.AddQuote("Press \"I\" to get info");
        }
        else if (troops.getUnit(y1, x1)->unUsed())
        {
            side.setMenuOption(abilities);
            drawAll();
            selector();
            exit = true;
        }
        else
        {
            Dial.AddQuote("This unit does not have a skill point");
        }
    }
    if (!exit)
    {
        drawAll();
        choose(y1, x1);
    }
}

void GMGameMenu::manipulator_equip(eControls controls)
{
    bool exit = false;
    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        if (y1 != 1)
        {
            y1 = 1;
        }
        else
        {
            y1 = 0;
        }
    }

    if (controls == eControls::LEFT)
    {
        if (x1 > 0)
        {
            x1--;
        }
        else
        {
            x1 = 3;
        }
    }

    if (controls == eControls::RIGHT)
    {
        if (x1 < 3)
        {
            x1++;
        }
        else
        {
            x1 = 0;
        }
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(options::battle);
    }

    if (controls == eControls::SUBMIT)
    {
        if (troops.getUnit(y1, x1)->getType() != untitled)
        {
            drawInventory();
            itemSelector();
            side.setMenuOption(options::sorting);
            exit = true;
        }
        else
        {
            Dial.AddQuote("You should select a Unit.");
        }
    }

    if (!exit)
    {
        drawAll();
        choose(y1, x1);
    }
}

void GMGameMenu::blink(const int position, bool present)
{
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            if (present)
            {
                screen[5 + j][i + 2 + position * 11] = ' ';
            }
            else
            {
                screen[5 + j][i + 2 + position * 11] = horde.getUnit(position)->getPic(j, i);
            }
        }
    }
}

void GMGameMenu::massAttack(const int Dmg)
{
    int countDown = 8;

    for (int i = 0; i < 4; i++)
    {
        if (horde.exists(3 - i) || horde.exists(4 + i))
        {
            countDown = 8;
            while (countDown)
            {
                if (horde.exists(3 - i))
                {
                    blink(3 - i, countDown % 2);
                }
                if (horde.exists(4 + i))
                {
                    blink(4 + i, countDown % 2);
                }
                print();
                countDown--;
                Sleep(120);
            }
            if (horde.exists(3 - i))
            {
                horde.getUnit(3 - i)->damage(Dmg);
            }
            if (horde.exists(4 + i))
            {
                horde.getUnit(4 + i)->damage(Dmg);
            }
            drawUndead();
        }
    }
}

void GMGameMenu::splash(const int dmg, const int splash)
{
    if (splash)
    {
        if (horde.exists(x1 - 1) || horde.exists(x1 + 1))
        {
            int countDown = 8;

            while (countDown)
            {
                if (horde.exists(x1 - 1))
                {
                    blink(x1 - 1, countDown % 2);
                }
                if (horde.exists(x1 + 1))
                {
                    blink(x1 + 1, countDown % 2);
                }
                print();
                countDown--;
                Sleep(130);
            }

            int s = (dmg * splash) / 100;

            if (horde.exists(x1 - 1))
            {
                horde.getUnit(x1 - 1)->damage(s);
            }
            if (horde.exists(x1 + 1))
            {
                horde.getUnit(x1 + 1)->damage(s);
            }
            drawUndead();
        }
    }
}

void GMGameMenu::manipulator_Slashing(eControls controls)
{
    bool exit = false;
    int last = horde.getCount() - 1;

    if (horde.getCount() > 7)
    {
        last = 7;
    }

    int g;
    g = getchar();

    if (controls == eControls::LEFT)
    {
        x1--;
        if (x1 < 0)
        {
            x1 = last;
        }
        while (horde.getUnit(x1)->getType() == wasted)
        {
            x1--;
            if (x1 < 0)
            {
                x1 = last;
            }
        }
    }

    if (controls == eControls::RIGHT)
    {
        x1++;
        if (x1 > last)
        {
            x1 = 0;
        }
        while (horde.getUnit(x1)->getType() == wasted)
        {
            x1++;
            if (x1 > last)
            {
                x1 = 0;
            }
        }
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(options::attacking);
        exit = true;
    }

    if (controls == eControls::SUBMIT)
    {
        attack();
        resetVariables();
        whosTurn();
        exit = true;
    }

    drawUndead();

    if (!exit)
    {
        drawAll();
        zombieSelector();
        selector();
    }
}

void GMGameMenu::manipulator_Bombing(eControls controls)
{
    bool exit = false;
    int last = horde.getCount() - 1;

    if (horde.getCount() > 7)
    {
        last = 7;
    }

    int g;
    g = getchar();

    if (controls == eControls::LEFT)
    {
        x1--;
        if (x1 < 0)
        {
            x1 = last;
        }
        while (horde.getUnit(x1)->getType() == wasted)
        {
            x1--;
            if (x1 < 0)
            {
                x1 = last;
            }
        }
    }

    if (controls == eControls::RIGHT)
    {
        x1++;
        if (x1 > last)
        {
            x1 = 0;
        }
        while (horde.getUnit(x1)->getType() == wasted)
        {
            x1++;
            if (x1 > last)
            {
                x1 = 0;
            }
        }
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(options::sorting);
        exit = true;
    }

    if (controls == eControls::SUBMIT)
    {
        clear();
        drawAll();
        drawUndead();
        selector();
        usable->consume();
        slashedAnimation(usable->getProperty());
        splash(usable->getProperty(), 50);
        troops.getAttacker()->usedTurn();
        side.setMenuOption(attacking);
        resetVariables();
        whosTurn();
    }

    drawUndead();

    if (!exit)
    {
        drawAll();
        zombieSelector();
        selector();
    }
    else
    {
        clear();
        drawInventory();
        itemSelector();
    }
}

void GMGameMenu::healingAnimation()
{
    int count = 0;
    char buff[16][20] =
    {
        "+     +        +   ",
        "   +       +    +  ",
        "  +                ",
        "        +     +    ",
        "  +        +      +",
        "       +           ",
        "   +           +   ",
        "+       +    +     ",
        "  +        +     + ",
        "   +  +       +    ",
        "+          +       ",
        "      +         +  ",
        "  +        +      +",
        "       +           ",
        "   +      +    +   ",
        "+       +    +     "
    };

    char front[4][20] =
    {
        "         __        ",
        "       _|**|_      ",
        "      |_****_|     ",
        "        |__|       ",
    };

    for (int j = 0; j < 16; j++)
    {
        for (int i = 0; i < 20; i++)
        {
            if (buff[j][i] == '+')
            {
                buff[j][i] = char(1);
            }
        }
    }

    while (count < 16)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < 19; i++)
            {
                if (j + count % 17 >= 16)
                {
                    CharOut(buff[(j + count - 8) % 17][i], j + BottomPlank + y1 * 10 - 19, i + x1 * 22 + 3);
                }
                else
                {
                    CharOut(buff[(j + count) % 17][i], j + BottomPlank + y1 * 10 - 19, i + x1 * 22 + 3);
                }
            }
        }
        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 19; i++)
            {
                if (front[j][i] == '*')
                {
                    CharOut(' ', j + BottomPlank + y1 * 10 - 18, i + x1 * 22 + 3);
                }
                else if (front[j][i] != ' ')
                {
                    CharOut(front[j][i], j + BottomPlank + y1 * 10 - 18, i + x1 * 22 + 3);
                }
            }
        }
        count++;
        Sleep(100);
        print();
    }
    drawAll();
}

void GMGameMenu::ZombieBiteAninmation()
{
    int count = 16;

    char front[2][9] =
    {
        " \\/\\/\\/ ",
        "  /\\/\\  "
    };

    x1 = horde.getAttackerPos();

    while (count > 0)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                CharOut(' ', j + 6, i + 3 + x1 * 11);

                if (count % 2 == 0 && j == 3)
                {
                    CharOut(front[0][i], j + 6, i + 3 + x1 * 11);
                }
                else if (count % 2 == 0 && j == 4)
                {
                    CharOut(front[1][i], j + 6, i + 3 + x1 * 11);
                }
                if (count % 2 == 1 && j == 2)
                {
                    CharOut(front[0][i], j + 6, i + 3 + x1 * 11);
                }
                else if (count % 2 == 1 && j == 5)
                {
                    CharOut(front[1][i], j + 6, i + 3 + x1 * 11);
                }
            }
        }

        count--;
        Sleep(100);
        print();
    }
}

void GMGameMenu::massHealAnimation()
{
    int count = 0;
    char buff[16][20] =
    {
        "+     +        +   ",
        "   +       +    +  ",
        "  +                ",
        "        +     +    ",
        "  +        +      +",
        "       +           ",
        "   +           +   ",
        "+       +    +     ",
        "  +        +     + ",
        "   +  +       +    ",
        "+          +       ",
        "      +         +  ",
        "  +        +      +",
        "       +           ",
        "   +      +    +   ",
        "+       +    +     "
    };

    char front[4][20] =
    {
        "         __        ",
        "       _|**|_      ",
        "      |_****_|     ",
        "        |__|       ",
    };

    for (int j = 0; j < 16; j++)
    {
        for (int i = 0; i < 20; i++)
        {
            if (buff[j][i] == '+')
            {
                buff[j][i] = char(1);
            }
        }
    }

    int y = 0;
    int x = 0;

    while (count < 16)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < 19; i++)
            {
                for (int k = 0; k < 8; k++)
                {
                    y = k / 4;
                    x = k % 4;
                    if (troops.getUnit(k)->getType() && troops.getUnit(k)->IsAlive())
                    {
                        if (j + count % 17 >= 16)
                        {
                            CharOut(buff[(j + count - 8) % 17][i], j + BottomPlank + y * 10 - 19, i + x * 22 + 3);
                        }
                        else
                        {
                            CharOut(buff[(j + count) % 17][i], j + BottomPlank + y * 10 - 19, i + x * 22 + 3);
                        }
                    }
                }
            }
        }
        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 19; i++)
            {
                for (int k = 0; k < 8; k++)
                {
                    y = k / 4;
                    x = k % 4;
                    if (troops.getUnit(k)->getType() && troops.getUnit(k)->IsAlive())
                    {
                        if (front[j][i] == '*')
                        {
                            CharOut(' ', j + BottomPlank + y * 10 - 18, i + x * 22 + 3);
                        }
                        else if (front[j][i] != ' ')
                        {
                            CharOut(front[j][i], j + BottomPlank + y * 10 - 18, i + x * 22 + 3);
                        }
                    }
                }
            }
        }
        count++;
        Sleep(100);
        print();
    }
    drawAll();
}

void GMGameMenu::ZombiePirsAnimation()
{
    int count = 0;
    char buff[8][9] =
    {
        "   |    ",
        " |   |  ",
        "|  |    ",
        "  |  | |",
        "        ",
        "|  |  | ",
        " |   |  ",
        "  |    |"
    };
    char front[4][9] =
    {
    " /|/|/| ",
    " |||||| ",
    " |||||| ",
    " \\|\\|\\| "
    };
    while (count < 16)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                if (j - count % 9 < 0)
                {
                    CharOut(buff[j - count % 9 + 8][i], j + 6, i + 3 + x1 * 11);
                }
                else
                {
                    CharOut(buff[j - count % 9][i], j + 6, i + 3 + x1 * 11);
                }
            }
        }

        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                if (front[j][i] != ' ')
                {
                    CharOut(front[j][i], j + 8, i + 3 + x1 * 11);
                }
            }
        }
        count++;
        Sleep(100);
        print();
    }
}

void GMGameMenu::ZombieBuffAnimation()
{
    int count = 0;
    char buff[3][9] =
    {
    "   /\\   ",
    "  /  \\  ",
    " / /\\ \\ "
    };

    while (count < 16)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                CharOut(buff[(j + count) % 3][i], j + 6, i + 3 + x1 * 11);
            }
        }
        count++;
        Sleep(1000);
        print();
    }
    drawUndead();
}

void GMGameMenu::stun()
{
    int stunned = troops.getAttacker()->getStuned();
    if (horde.exists(x1))
    {
        if (stunned)
        {
            ZombieStunnedAnimation();
            horde.getUnit(x1)->setStunned(stunned);
        }
    }
    drawUndead();
}

void GMGameMenu::pirs()
{
    int pirs = troops.getAttacker()->getPirs();
    if (pirs)
    {
        if (horde.exists(x1))
        {
            if (pirs * 3 > horde.getUnit(x1)->getBleedDmg())
            {
                ZombiePirsAnimation();
                horde.getUnit(x1)->setBleeding(3, pirs);
            }
        }
    }
    drawUndead();
}

void GMGameMenu::crit()
{
    int crit = (troops.getAttacker()->getCrited()) * (troops.getAttacker()->getDamage()) / 100;
    if (crit)
    {
        ZombieCritAnimation();
        horde.getUnit(x1)->damage(crit);
    }
    else
    {
        slashedAnimation(troops.getAttacker()->getDamage());
    }
    drawUndead();
}

void GMGameMenu::attack()
{
    clear();
    drawAll();
    drawUndead();
    selector();
    crit();
    stun();
    pirs();
    splash(troops.getAttacker()->getDamage(), troops.getAttacker()->getSplash());
    troops.getAttacker()->usedTurn();
    side.setMenuOption(attacking);
}

void GMGameMenu::massHeal(const int factor)
{
    for (int row = 0; row < 2; row++)
    {
        for (int card = 0; card < 4; card++)
        {
            if (troops.getUnit(row, card)->getType() != untitled && troops.getUnit(row, card)->IsAlive())
            {
                troops.getUnit(row, card)->HpUp(factor);
                troops.getUnit(row, card)->picture();
            }
        }
    }
}

void GMGameMenu::manipulator_Choosing(eControls controls)
{
    bool exit = false;
    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        if (y1 != 1)
        {
            y1 = 1;
        }
        else
            y1 = 0;
    }

    if (controls == eControls::LEFT)
    {
        if (x1 > 0)
        {
            x1--;
        }
        else
        {
            x1 = 3;
        }
    }

    if (controls == eControls::RIGHT)
    {
        if (x1 < 3)
        {
            x1++;
        }
        else
        {
            x1 = 0;
        }
    }

    if (controls == eControls::QUIT)
    {
        if (side.getMenuOption() == options::choosing)
        {
            if (capture)
            {
                capture = false;
            }
            else
            {
                clear();
                drawAll();
                drawUndead();
                print();
                side.setMenuOption(options::battle);
                exit = true;
            }
        }
        else
        {
            side.setMenuOption(options::attacking);
            exit = true;
            revive = false;
            drawAll();
            drawUndead();
            selector();
        }
    }

    if (controls == eControls::SUBMIT)
    {
        if (side.getMenuOption() == options::choosing)
        {
            if (capture)
            {
                swapCards(y1, x1, y2, x2);
                capture = false;
            }
            else
            {
                x2 = x1;
                y2 = y1;
                capture = true;
            }
        }
        else
        {
            clear();
            if (troops.getUnit(y1, x1)->IsAlive() && !revive)
            {
                troops.getUnit(y1, x1)->HpUp(troops.getAttacker()->getAbility(3) * 100);
                troops.getAttacker()->usedTurn();
                side.setMenuOption(options::attacking);
                exit = true;
                drawAll();
                drawUndead();
                healingAnimation();
                whosTurn();
                selector();
            }
            else if (!troops.getUnit(y1, x1)->IsAlive() && !revive)
            {
                drawAll();
                drawUndead();
                Dial.AddQuote("This would not help. He is dead");
            }
            else if (!troops.getUnit(y1, x1)->IsAlive() && revive)
            {
                troops.getUnit(y1, x1)->revive();
                int hp = (troops.getUnit(y1, x1)->getMaxHp() * (10 * troops.getAttacker()->getAbility(5))) / 100;
                troops.getUnit(y1, x1)->HpUp(hp);
                troops.getAttacker()->usedTurn();
                side.setMenuOption(options::attacking);
                exit = true;
                revive = false;
                drawAll();
                drawUndead();
                healingAnimation();
                whosTurn();
                selector();
            }
            else
            {
                drawAll();
                drawUndead();
                Dial.AddQuote("You can not bring to live someone who's not dead");
            }
        }
    }
    if (!exit)
    {
        drawAll();
        choose(y1, x1);
    }
    if (capture == true)
    {
        choose(y2, x2);
    }
}

void GMGameMenu::manipulator_firstAid(eControls controls)
{
    bool exit = false;

    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        if (y1 != 1)
        {
            y1 = 1;
        }
        else
            y1 = 0;
    }

    if (controls == eControls::LEFT)
    {
        if (x1 > 0)
        {
            x1--;
        }
        else
        {
            x1 = 3;
        }
    }

    if (controls == eControls::RIGHT)
    {
        if (x1 < 3)
        {
            x1++;
        }
        else
        {
            x1 = 0;
        }
    }

    if (controls == eControls::QUIT)
    {
        clear();
        side.setMenuOption(options::sorting);
        drawInventory();
        itemSelector();
        exit = true;
    }

    if (controls == eControls::SUBMIT)
    {
        clear();
        if (troops.getUnit(y1, x1)->IsAlive() && !revive && troops.getUnit(y1, x1)->IsDamaged())
        {
            usable->consume();
            troops.getUnit(y1, x1)->HpUp(usable->getProperty());
            troops.getAttacker()->usedTurn();
            side.setMenuOption(options::attacking);
            drawAll();
            drawUndead();
            healingAnimation();
            whosTurn();
            selector();
            exit = true;
        }
        else if (troops.getUnit(y1, x1)->IsAlive() && !revive && !troops.getUnit(y1, x1)->IsDamaged())
        {
            drawAll();
            drawUndead();
            Dial.AddQuote("This unit is in good health");
        }
        else if (!troops.getUnit(y1, x1)->IsAlive() && !revive)
        {
            drawAll();
            drawUndead();
            Dial.AddQuote("This would not help. He is dead");
        }
        else if (!troops.getUnit(y1, x1)->IsAlive() && revive)
        {
            troops.getUnit(y1, x1)->revive();
            troops.getUnit(y1, x1)->HpUp(usable->getProperty());
            troops.getAttacker()->usedTurn();
            side.setMenuOption(options::attacking);
            exit = true;
            revive = false;
            drawAll();
            drawUndead();
            healingAnimation();
            whosTurn();
            selector();
        }
        else
        {
            drawAll();
            drawUndead();
            Dial.AddQuote("You can not bring to live someone who's not dead");
        }
    }
    if (!exit)
    {
        drawAll();
        choose(y1, x1);
    }
}

void GMGameMenu::manipulator_Battle(eControls controls)
{
    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        side.slider(controls);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == options::begin)
    {
        side.setMenuOption(options::attacking);
        setUndead();
        troops.allFine();
        resetVariables();
        drawAll();
        battle = true;
        drawUndead();
        resetTurns();
        selector();
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == options::swap)
    {
        hide();
        drawAll();
        resetVariables();
        choose(y1, x1);
        side.setMenuOption(options::choosing);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == options::lvl)
    {
        hide();
        resetVariables();
        side.setMenuOption(options::upgrading);
        drawAll();
        choose(y1, x1);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == options::feed)
    {
        if (Res.getFood() < troops.rollcall() * 3 + farmers.getcount() * 2 + allMissingHp())
        {
            Dial.AddQuote("You dont have enough food to feed your troops");
        }
        else
        {
            Res.addFood(-(troops.rollcall() * 1 + farmers.getcount() * 2 + allMissingHp()));
            for (int row = 0; row < 2; row++)
            {
                for (int card = 0; card < 4; card++)
                {
                    troops.getUnit(row, card)->OverHeal();
                    troops.getUnit(row, card)->picture();
                }
            }
            drawAll();
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == options::hire)
    {
        if (!possession.getRoad() && !possession.getBarracks())
        {
            Dial.AddQuote("In order to equip and train your units");
            Dial.AddQuote("You need to get access to the shop first! Build tunel and baraks.");
        }
        else
        {
            if (farmers.getcount() < 2)
            {
                Dial.AddQuote("You don't have people to train");
            }
            else
            {
                if (Res.getMoney() < 500)
                {
                    Dial.AddQuote("You dont have enough money to buy equipment (500)");
                }
                else
                {
                    Res.addMoney(-500);
                    farmers.death(0);
                    addUnit();
                }
            }
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == options::equip)
    {
        hide();
        resetVariables();
        side.setMenuOption(options::equiping);
        drawAll();
        choose(y1, x1);
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(options::main);
        clear();
        reveal();
    }

    if (controls == eControls::CLEAR)
    {
        Dial.clearBox();
        showDialog();
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(options::main);
    }
}

void GMGameMenu::resetVariables()
{
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    usable = nullptr;
}

int GMGameMenu::allMissingHp()
{
    int wounds = 0;
    for (int row = 0; row < 2; row++)
    {
        for (int card = 0; card < 4; card++)
        {
            wounds += troops.getUnit(row, card)->missingHP();
        }
    }
    return wounds;
}

void GMGameMenu::massExp(const int factor)
{
    for (int row = 0; row < 2; row++)
    {
        for (int card = 0; card < 4; card++)
        {
            if (troops.getUnit(row, card)->getType() != untitled)
            {
                troops.getUnit(row, card)->add_exp(factor);
            }
        }
    }
}

void GMGameMenu::manipulator_Work(eControls controls)
{
    side.clear();

    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        side.slider(controls);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == chop)
    {
        if (!farmers.freeFarmers())
        {
            Dial.AddQuote("Sorry buddy, but you are out of farmers!");
        }
        else
        {
            Dial.AddQuote("Your farmer went into the woods");
            list.AddWork(farmers.checkForFreeFarmer(), Dial, chop, Res);
            showDialog();
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == adventure)
    {
        if (!farmers.freeFarmers())
        {
            Dial.AddQuote("Sorry boddy, but you are out of farmers!");
        }
        else
        {
            Dial.AddQuote("Your farmer went on an adventure");
            list.AddWork(farmers.checkForFreeFarmer(), Dial, adventure, Res);
            showDialog();
        }
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == collect)
    {
        if (!farmers.checkForFreeFarmer())
        {
            Dial.AddQuote("Sorry boddy, but you are out of farmers!");
        }
        else
        {
            if ((list.getHead() == nullptr) || (list.getHead()->show_progress() == false))
            {
                Dial.AddQuote("There is nothing to collect on the field");
            }
            else if (Animation.getDone() != chill)
            {
                Dial.AddQuote("You are already working on a field");
            }
            else
            {
                side.clear();
                print();
                Animation.startCollecting(farmers.checkForFreeFarmer());
                mapResources();
            }
        }
        showDialog();
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == shop)
    {
        if (!possession.getRoad())
        {
            Dial.AddQuote("The Tunel is required in order to access the Shop");
            showDialog();
        }
        else
        {
            side.setMenuOption(shopping);
        }
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(options::main);
    }

    if (controls == eControls::CLEAR)
    {
        Dial.clearBox();
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(options::main);
    }

}

void GMGameMenu::clear()
{
    for (int j = 4; j < BottomPlank; j++)
    {
        for (int i = 1; i < SidePlank; i++)
        {
            screen[j][i] = ' ';
        }
    }
}

void GMGameMenu::manipulator_Exit(eControls controls)
{
    side.clear();

    if (controls == eControls::DOWN || controls == eControls::UP)
    {
        side.slider(controls);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == yes)
    {
        Dial.AddQuote("Cya");
        showDialog();
        print();
        exit(0);
    }

    if ((controls == eControls::SUBMIT) && side.getOption() == no)
    {
        side.setMenuOption(main);
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(1);
    }

    if (controls == eControls::CLEAR)
    {
        Dial.clearBox();
    }

    if (controls == eControls::QUIT)
    {
        side.setMenuOption(options::main);
    }

}

void GMGameMenu::hide()
{
    clear();
    MyField.hide();
    possession.hide();
    Animation.hide();
}

void GMGameMenu::reveal()
{
    MyField.reveal();
    MyField.BuildFence();
    MyField.showField();
    possession.reveal();
    possession.buildHome();
    Animation.reveal();
    if (possession.getRoad())
    {
        possession.buildRoad();
    }
    if (possession.getBarracks())
    {
        possession.buildBaracks();
    }
    if (possession.getTentSize() != noTent)
    {
        possession.buildTent();
    }
}
GMGameMenu::GMGameMenu(bool Loading, engine* engine, char** screen) :
    MyField(screen),
    NightRaid(0),
    Animation(screen, MyField, list, Res, Dial),
    stock(Dial),
    plant(potato),
    SidePlank(ScreenSize::SidePlank),
    BottomPlank(ScreenSize::BottomPlank),
    possession(screen),
    Res(possession),
    progress(screen, list),
    animate(false),
    revive(false),
    selling(false),
    battle(false),
    store(wood),
    capture(false),
    usable(nullptr),
    GMBase(engine, screen)
{
    resetVariables();
    clear();
    for (int j = 1; j < y - 1; j++)
    {
        screen[BottomPlank][j] = '_';
    }

    for (int j = 1; j < y - 1; j++)
    {
        screen[3][j] = '_';
    }

    for (int j = 1; j < x; j++)
    {
        screen[j][SidePlank] = '|';
    }

    for (int i = 0; i < strlen(texts_1::day); i++)
    {
        screen[2][(SidePlank + i) + 2] = texts_1::day[i];
    }

    for (int i = 0; i < strlen(texts_1::time); i++)
    {
        screen[2][(y + i) - (strlen(texts_1::day) + 10)] = texts_1::time[i];
    }
    screen[2][y - 5] = ':';

    int position = 3;

    for (int i = 0; i < strlen(texts_1::wood); i++)
    {
        screen[2][(position)] = texts_1::wood[i];
        position++;
    }
    position += Res.getSpace();

    for (int i = 0; i < strlen(texts_1::seeds); i++)
    {
        screen[2][(position)] = texts_1::seeds[i];
        position++;
    }
    position += Res.getSpace();

    for (int i = 0; i < strlen(texts_1::food); i++)
    {
        screen[2][(position)] = texts_1::food[i];
        position++;
    }
    position += Res.getSpace();

    for (int i = 0; i < strlen(texts_1::money); i++)
    {
        screen[2][(position)] = texts_1::money[i];
        position++;
    }
    position += Res.getSpace();

    for (int i = 0; i < strlen(texts_1::farmers); i++)
    {
        screen[2][(position)] = texts_1::farmers[i];
        position++;
    }
    position += Res.getSpace();
    possession.buildHome();
    MyField.BuildFence();

    srand(unsigned(time(NULL)));

    progress.clear();
    MyField.showField();

    if (Loading)
    {
        load();
        troops.drawAll();
    }
    else
    {
        farmers.hire();
        farmers.hire();

        troops.addSolder(0, 0, 10);
        troops.addSolder(0, 1, 10);
        troops.addSolder(0, 2, 10);
        infoScreen();
        show();
    }
}

void GMGameMenu::setUndead()
{
    horde.setMoney();
    horde.setExp();

    float factor = 1;
    int money = 0;
    int exp = 0;

    srand(unsigned(time(NULL)));

    int lvl = GlobalTime.getDay();

    if (lvl > 25)
    {
        lvl = 25;
    }

    switch (GlobalTime.getDTime())
    {
    case DayTime::Dawn:
        factor = 2.5f;
        break;

    case DayTime::Night:
        factor = 2.0f;
        break;

    default:
        factor = 1.0f;
    }
    int numberOfUndead = (farmers.getcount() / 4 + troops.rollcall() / 2 + GlobalTime.getDay() / 2.5) * factor + 4;

    if (numberOfUndead > 24)
    {
        numberOfUndead = 24;
    }

    if (numberOfUndead >= GlobalTime.getDay() / 2.5 && GlobalTime.getDay() >= 2)
    {
        for (int i = 0; i < GlobalTime.getDay() / 2.5; i++)
        {
            horde.addLurker(lvl + rand() % 4);
            money += (25 + lvl * 3);
            exp += (20 + lvl * 4);
            numberOfUndead--;
        }

        if (numberOfUndead >= GlobalTime.getDay() / 3 && GlobalTime.getDay() >= 3)
        {
            for (int i = 0; i < GlobalTime.getDay() / 3; i++)
            {
                horde.addGhoul(lvl);
                money += (50 + lvl * 4);
                exp += (25 + lvl * 6);
                numberOfUndead--;
            }

            if (numberOfUndead >= GlobalTime.getDay() / 3.5 && GlobalTime.getDay() >= 3)
            {
                for (int i = 0; i < GlobalTime.getDay() / 3.5; i++)
                {
                    horde.addBasher(lvl);
                    money += (150 + lvl * 9);
                    exp += (80 + lvl * 11);
                    numberOfUndead--;
                }

                if (numberOfUndead >= GlobalTime.getDay() / 4 && GlobalTime.getDay() >= 4)
                {
                    for (int i = 0; i < GlobalTime.getDay() / 4; i++)
                    {
                        horde.addLeaper(lvl);
                        money += (100 + lvl * 10);
                        exp += (200 + lvl * 12);
                        numberOfUndead--;
                    }
                }
            }
        }
    }
    while (numberOfUndead > 0)
    {
        horde.addWalker(GlobalTime.getDay());
        money += (15 + lvl * 3);
        exp += (10 + lvl * 4);
        numberOfUndead--;
    }

    bool remainder = horde.getCount() % 8;
    int waves = horde.getCount() / 8 + remainder;
    horde.setNumberOfWaves(waves);
    horde.setWave(1);

    horde.randomize();
    horde.setMoney(money);
    horde.setExp(exp);

    showWaves();
}

void GMGameMenu::showWaves()
{
    if (horde.getWave())
    {
        int l = 0;
        char waves[] = "Wave";
        for (int i = 0; i < 4; i++)
        {
            CharOut(waves[i], 4, SidePlank / 2 + l);
            l++;
        }
        int wave = horde.getWave();
        l += LenOfNumbers(horde.getWave());
        for (int i = 0; i < LenOfNumbers(horde.getWave()); i++)
        {
            CharOut(wave % 10, 4, SidePlank / 2 + l);
            l--;
            wave /= 10;
        }
        l += LenOfNumbers(horde.getWave());
        l++;
        CharOut('/', 4, SidePlank / 2 + l);
        l += LenOfNumbers(horde.getNumberOfWaves());
        wave = horde.getNumberOfWaves();
        for (int i = 0; i < LenOfNumbers(horde.getNumberOfWaves()); i++)
        {
            CharOut(wave % 10, 4, SidePlank / 2 + l);
            l--;
            wave /= 10;
        }
    }
}

void GMGameMenu::drawUndead()
{
    int last = horde.getCount();
    if (horde.getCount() / 8)
    {
        last = 8;
    }

    for (int card = 0; card < last; card++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int i = 0; i < 10; i++)
            {
                if (horde.getUnit(card)->getType() != zombies::blank)
                {
                    screen[5 + j][2 + i + card * 11] = horde.getUnit(card)->getPic(j, i);
                }
                else
                {
                    screen[5 + j][2 + i + card * 11] = ' ';
                }
            }
        }
    }

    if (!horde.getHead())
    {
        side.setMenuOption(options::battle);
    }
    else if (checkWasted())
    {
        deleteWaves();
    }
}

bool GMGameMenu::isPlant(const char* name) const
{
    bool is = false;

    for (int j = 0; j < numberOfPlants; j++)
    {
        if (equals(plants[j], name))
        {
            is = true;
            j = numberOfPlants;
        }
    }

    return is;
}

bool GMGameMenu::isJob(const char* name) const
{
    bool is = false;

    for (int j = 0; j < numberOfJobs; j++)
    {
        if (equals(jobs[j], name))
        {
            is = true;
            j = numberOfJobs;
        }
    }

    return is;
}

void GMGameMenu::controlSignal(eControls controls)
{
    switch (side.getMenuOption()) {
        case options::main:
            manipulator_Main(controls);
            break;
        case options::planting:
            manipulator_Plants(controls);
            break;
        case options::building:
            manipulator_Building(controls);
            break;
        case options::working:
            manipulator_Work(controls);
            break;
            case options::quiting:
            manipulator_Exit(controls);
            break;
        case options::plantSelectorStart:
            manipulator_Select(controls);
            break;
        case options::plantSelectorEnd:
            manipulator_Capture(controls);
            break;
        case options::shopping:
            manipulator_Shop(controls);
            break;
        case options::sell:
            manipulator_Sell(controls);
            break;
        case options::buy:
            manipulator_Buy(controls);
            break;
        case options::amount:
            manipulator_Amount(controls);
            break;
        case options::choosing:
            manipulator_Choosing(controls);
            break;
        case options::battle:
            manipulator_Battle(controls);
            break;
        case options::lvling:
            manipulator_lvling(controls);
            break;
        case options::upgrading:
            manipulator_upgrading(controls);
            break;
        case options::slashing:
            manipulator_Slashing(controls);
            break;
        case options::attacking:
            manipulator_Attack(controls);
            break;
        case options::equiping:
            manipulator_equip(controls);
            break;
        case options::sorting:
            manipulator_Inventory(controls);
            break;
        case options::healing:
            manipulator_Choosing(controls);
            break;
        case options::bombing:
            manipulator_Bombing(controls);
            break;
        case options::firstAid:
            manipulator_firstAid(controls);
            break;
        case options::abilities:
            manipulator_Abilities(controls);
            break;
        default:
			break;
    }
}

void GMGameMenu::Draw(float fElapsedTime)
{
    GlobalTime.fly(fElapsedTime);
    progress.showProgress(fElapsedTime);
    functional();
    show();
}

bool GMGameMenu::isBuilding(const char* name) const
{
    bool is = false;

    for (int j = 0; j < numberOfBuildings; j++)
    {
        if (equals(buildings[j], name))
        {
            is = true;
            j = numberOfBuildings;
        }
    }

    return is;
}

void GMGameMenu::save()
{
    ofstream saveFile("/Users/1mperec/Desktop/Веселый Зомби Фермер/Save.txt");
    saveFile << possession.getHouseSize() << '\n' << possession.getRoad() << '\n' << MyField.getSize() << '\n';
    saveFile << possession.getTentSize() << '\n' << possession.getBarracks() << '\n';
    saveFile << Res.getWood() << '\n' << Res.getFood() << '\n' << Res.getSeeds() << '\n' << Res.getMoney() << '\n' << farmers.getcount() << '\n';
    saveFile << GlobalTime.getDay() << '\n' << GlobalTime.getHour() << '\n' << GlobalTime.getMin() << '\n';
    saveFile.close();

    ofstream Units("/Users/1mperec/Desktop/Веселый Зомби Фермер/Units.txt");
    for (int row = 0; row < 2; row++)
    {
        for (int card = 0; card < 4; card++)
        {
            Units << troops.getUnit(row, card)->getType() << '\n' << troops.getUnit(row, card)->getLvl() << '\n';
            Units << troops.getUnit(row, card)->getExp() << '\n' << troops.getUnit(row, card)->gethealth() << '\n';
            Units << troops.getUnit(row, card)->getAbility(1) << ' ' << troops.getUnit(row, card)->getAbility(2) << ' ';
            Units << troops.getUnit(row, card)->getAbility(3) << ' ' << troops.getUnit(row, card)->getAbility(4) << ' ';
            Units << troops.getUnit(row, card)->getAbility(5) << '\n';
        }
    }
    Units.close();
    ofstream Eve("/Users/1mperec/Desktop/Веселый Зомби Фермер/Eve.txt");

    Eve << list.getCount() << '\n';
    event* aloc = list.getHead();
    for (int i = 0; i < list.getCount(); i++)
    {

        if (isPlant(aloc->getName()))
        {
            //            plant
            Eve << aloc->getName() << '\n';
            Eve << aloc->getOption() << '\n';
            Eve << aloc->getDay() << '\n';
            Eve << aloc->getHour() << '\n';
            Eve << aloc->getMin() << '\n';
            int l = unsigned(strlen(aloc->getMatrix()[0]));
            Eve << l << '\n';
            for (int j = 0; j < l; j++)
            {
                for (int i = 0; i < l; i++)
                {
                    if (aloc->getMatrix()[j][i] == ' ')
                    {
                        Eve << '*';
                    }
                    else
                    {
                        Eve << aloc->getMatrix()[j][i];
                    }
                }
                Eve << '\n';
            }
        }

        else if (isJob(aloc->getName()))
        {
            //Job
            Eve << aloc->getName() << '\n';
            Eve << aloc->getOption() << '\n';
            Eve << aloc->getDay() << '\n';
            Eve << aloc->getHour() << '\n';
            Eve << aloc->getMin() << '\n';
        }

        else if (isBuilding(aloc->getName()))
        {
            //Building
            Eve << aloc->getName() << '\n';
            Eve << aloc->getOption() << '\n';
            Eve << aloc->getDay() << '\n';
            Eve << aloc->getHour() << '\n';
            Eve << aloc->getMin() << '\n';
        }

        else
        {
            Dial.AddQuote("Something went wrong!");
            exit(0);
        }

        aloc = aloc->getNext();
    }

    Eve.close();

    ofstream Inventory("/Users/1mperec/Desktop/Веселый Зомби Фермер/Inventory.txt");
    char buff[20];
    for (int ITEMS = 0; ITEMS < items.getCount(); ITEMS++)
    {
        for (int i = 0; i < 20; i++)
        {
            buff[i] = items.getItem(ITEMS)->getTitle(i);
        }
        Inventory << buff << ' ';
        for (int i = 0; i < 20; i++)
        {
            buff[i] = items.getItem(ITEMS)->getName(i);
        }
        deflation(buff);
        Inventory << buff << '\n';
    }
    Inventory.close();

    ofstream Equipment("/Users/1mperec/Desktop/Веселый Зомби Фермер/Equipment.txt");

    for (int Units = 0; Units < 8; Units++)
    {
        if (troops.getUnit(Units))
        {
            if (troops.getUnit(Units)->getHelmet())
            {
                for (int i = 0; i < 20; i++)
                {
                    buff[i] = troops.getUnit(Units)->getHelmet()->getName(i);
                }
                deflation(buff);
                Equipment << buff << '\n';
            }
            else
            {
                Equipment << '$' << '\n';
            }
            if (troops.getUnit(Units)->getChest())
            {
                for (int i = 0; i < 20; i++)
                {
                    buff[i] = troops.getUnit(Units)->getChest()->getName(i);
                }
                deflation(buff);
                Equipment << buff << '\n';
            }
            else
            {
                Equipment << '$' << '\n';
            }

            if (troops.getUnit(Units)->getGloves())
            {
                for (int i = 0; i < 20; i++)
                {
                    buff[i] = troops.getUnit(Units)->getGloves()->getName(i);
                }
                deflation(buff);
                Equipment << buff << '\n';
            }
            else
            {
                Equipment << '$' << '\n';
            }

            if (troops.getUnit(Units)->getBoots())
            {
                for (int i = 0; i < 20; i++)
                {
                    buff[i] = troops.getUnit(Units)->getBoots()->getName(i);
                }
                deflation(buff);
                Equipment << buff << '\n';
            }
            else
            {
                Equipment << '$' << '\n';
            }

            if (troops.getUnit(Units)->getWeapon())
            {
                for (int i = 0; i < 20; i++)
                {
                    buff[i] = troops.getUnit(Units)->getWeapon()->getName(i);
                }
                deflation(buff);
                Equipment << buff << '\n';
            }
            else
            {
                Equipment << '$' << '\n';
            }
        }
        else
        {
            Equipment << '$' << '\n' << '$' << '\n' << '$' << '\n' << '$' << '\n' << '$' << '\n';
        }
    }
    Equipment.close();
}

void GMGameMenu::load()
{
    ifstream saveFile("/Users/1mperec/Desktop/Веселый Зомби Фермер/Save.txt");
    int wood = 0;
    int food = 0;
    int seeds = 0;
    int money = 0;
    int farmer = 0;
    int tent = 0;
    int house = 0;
    int field = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    bool road = false;
    bool baracks = false;

    saveFile >> house;
    saveFile >> road;
    saveFile >> field;
    saveFile >> tent;
    saveFile >> baracks;

    if (road)
    {
        possession.buildRoad();
    }

    if (baracks)
    {
        possession.buildBaracks();
    }

    while (possession.getHouseSize() != house)
    {
        possession.upgradeHomeSize();
    }

    while (possession.getTentSize() != tent)
    {
        possession.upgradeTentSize();
    }

    while (MyField.getSize() != field)
    {
        MyField.upgrade();
    }

    saveFile >> wood;
    saveFile >> food;
    saveFile >> seeds;
    saveFile >> money;
    saveFile >> farmer;

    Res.load(wood, food, seeds, money);
    for (int i = 0; i < farmer; i++)
    {
        farmers.hire();
    }

    saveFile >> day;
    saveFile >> hour;
    saveFile >> minute;

    GlobalTime.load(day, hour, minute);

    saveFile.close();

    ifstream Units("/Users/1mperec/Desktop/Веселый Зомби Фермер/Units.txt");
    int type = 0;
    int lvl = 0;
    int exp = 0;
    int hp = 0;
    int points = 0;

    for (int row = 0; row < 2; row++)
    {
        for (int card = 0; card < 4; card++)
        {
            Units >> type;
            Units >> lvl;
            Units >> exp;
            Units >> hp;
            switch (type)
            {
            case 0:
                break;

            case 1:
                troops.addSolder(row, card, lvl, hp);
                troops.getUnit(row, card)->add_exp(exp);
                break;

            case 2:
                troops.addTank(row, card, lvl, hp);
                troops.getUnit(row, card)->add_exp(exp);
                break;

            case 3:
                troops.addSniper(row, card, lvl, hp);
                troops.getUnit(row, card)->add_exp(exp);
                break;

            case 4:
                troops.addHealer(row, card, lvl, hp);
                troops.getUnit(row, card)->add_exp(exp);
                break;
            }
            for (int j = 0; j < 5; j++)
            {
                Units >> points;
                for (int i = 0; i < points; i++)
                {
                    troops.getUnit(row, card)->lvl_up_ability(j + 1);
                }
            }
        }
    }
    Units.close();

    ifstream Eve("/Users/1mperec/Desktop/Веселый Зомби Фермер/Eve.txt");

    int  count = 0;
    int  option = 0;

    char buff[30];

    Eve >> count;
    for (int i = 0; i < count; i++)
    {
        Eve >> buff;
        if (isPlant(buff))
        {
            int l = 0;
            enum plants type;
            Eve >> option;

            switch (option)
            {
            case 0:
                type = potato;
                break;
            case 1:
                type = corn;
                break;
            case 2:
                type = tomato;
                break;
            case 3:
                type = carrot;
                break;
            case 4:
                type = pumpkin;
                break;
            case 5:
                type = cherry;
                break;

            default:
                Dial.AddQuote("Error!");
                exit(0);
                break;
            }

            Eve >> day;
            Eve >> hour;
            Eve >> minute;
            Eve >> l;

            int Size = l;
            char** Matrix = new char* [l];

            for (int i = 0; i < l; i++)
            {
                Matrix[i] = new char[l];
            }

            for (int j = 0; j < l; j++)
            {
                Eve >> std::ws; // skip any leading whitespace
                Eve.getline(Matrix[j], l + 1);
            }
            for (int j = 0; j < l; j++)
            {
                for (int i = 0; i < l; i++)
                {
                    if (Matrix[j][i] == '*')
                    {
                        Matrix[j][i] = ' ';
                    }
                }
            }

            list.AddPlant(MyField, Matrix, Size, Dial, type, day, hour, minute);

            for (int i = 0; i < l; i++)
            {
                delete[]Matrix[i];
            }
            delete[]Matrix;
        }

        else if (isJob(buff))
        {
            enum jobs type;
            Eve >> option;

            switch (option)
            {
            case 0:
                type = chop;
                break;
            case 1:
                type = adventure;
                break;
            default:
                Dial.AddQuote("Error!");
                exit(0);
                break;
            }
            Eve >> day;
            Eve >> hour;
            Eve >> minute;
            list.AddWork(farmers.checkForFreeFarmer(), Dial, type, Res, day, hour, minute);
        }

        else if (isBuilding(buff))
        {

            enum structures type;
            Eve >> option;

            switch (option)
            {
            case 0:
                type = structures::fence;
                break;
            case 1:
                type = structures::tunel;
                break;
            case 2:
                type = structures::house;
                break;
            case 3:
                type = structures::tent;
                break;
            case 4:
                type = structures::barracks;
                break;
            default:
                Dial.AddQuote("Error!");
                exit(0);
                break;
            }
            Eve >> day;
            Eve >> hour;
            Eve >> minute;
            list.AddBuilding(MyField, farmers.checkForFreeFarmer(), Dial, type, possession, screen, day, hour, minute);
        }
    }

    Eve.close();

    ifstream Inventory("/Users/1mperec/Desktop/Веселый Зомби Фермер/Inventory.txt");
    while (!Inventory.eof())
    {
        Inventory >> buff;

        if (equals(buff, "Weapon"))
        {
            Inventory >> buff;
            inflation(buff);
            items.addItem(loader.weapon(buff));
        }
        else if (equals(buff, "Helmet"))
        {
            Inventory >> buff;
            inflation(buff);
            items.addItem(loader.helmet(buff));
        }
        else if (equals(buff, "Chest"))
        {
            Inventory >> buff;
            inflation(buff);
            items.addItem(loader.chest(buff));
        }
        else if (equals(buff, "Gloves"))
        {
            Inventory >> buff;
            inflation(buff);
            items.addItem(loader.gloves(buff));
        }
        else if (equals(buff, "Boots"))
        {
            Inventory >> buff;
            inflation(buff);
            items.addItem(loader.boots(buff));
        }
        else
        {

        }
    }
    Inventory.close();

    ifstream Equipment("/Users/1mperec/Desktop/Веселый Зомби Фермер/Equipment.txt");

    for (int Units = 0; Units < 8; Units++)
    {
        unit* UNIT = troops.getUnit(Units);

        Equipment >> buff;
        if (buff[0] != '$')
        {
            inflation(buff);
            UNIT->equipHelmet(loader.helmet(buff));
        }
        Equipment >> buff;
        if (buff[0] != '$')
        {
            inflation(buff);
            UNIT->equipChest(loader.chest(buff));
        }
        Equipment >> buff;
        if (buff[0] != '$')
        {
            inflation(buff);
            UNIT->equipGloves(loader.gloves(buff));
        }
        Equipment >> buff;
        if (buff[0] != '$')
        {
            inflation(buff);
            UNIT->equipBoots(loader.boots(buff));
        }
        Equipment >> buff;
        if (buff[0] != '$')
        {
            inflation(buff);
            UNIT->equipWeapon(loader.weapon(buff));
        }
    }

    Equipment.close();
}

void GMGameMenu::showTime()
{
    CharOut(GlobalTime.getHour() / 10, 2, y - 7);
    CharOut(GlobalTime.getHour() % 10, 2, y - 6);

    CharOut(GlobalTime.getMin() / 10, 2, y - 4);
    CharOut(GlobalTime.getMin() % 10, 2, y - 3);

    CharOut(GlobalTime.getDay() / 10, 2, SidePlank + 7);
    CharOut(GlobalTime.getDay() % 10, 2, SidePlank + 8);

    if ((GlobalTime.getSec() % 30 == 0) && (side.getMenuOption() == options::battle))
    {
        troops.blincker();
    }

    if (GlobalTime.getDTime() == DayTime::Day)
    {
        CharOut(char(30), 2, (y - SidePlank) / 2 + SidePlank - 2);
    }
    else if (GlobalTime.getDTime() == DayTime::Dawn)
    {
        if (GlobalTime.getHour() == 5 && !GlobalTime.getMin() && !GlobalTime.getSec())
        {
            if (!battle)
            {
                Dial.AddQuote("Beware! They are comming");
            }
            else
            {
                Dial.AddQuote("Hold them back! Thats our only hope to survive");
            }
        }
        if (GlobalTime.getHour() == 5 && GlobalTime.getMin() == 30 && !GlobalTime.getSec())
        {
            NightRaid = true;
            if (!battle)
            {
                hide();
                side.setMenuOption(options::attacking);
                setUndead();
                troops.allFine();
                resetVariables();
                drawAll();
                battle = true;
                drawUndead();
                resetTurns();
                selector();
                show();
            }
        }
        CharOut(char(7), 2, (y - SidePlank) / 2 + SidePlank - 2);
    }
    else
    {
        CharOut(char(9), 2, (y - SidePlank) / 2 + SidePlank - 2);
    }
}
void GMGameMenu::CharOut(char ch, int i, int j)
{
    if (i < x && i>0 && j < y && j>0)
    {
        screen[i][j] = ch;
    }
}
void GMGameMenu::CharOut(int num, int i, int j)
{
    if (i < x && i>0 && j < y && j>0)
    {
        screen[i][j] = (char)((int)'0') + num;
    }
}
void GMGameMenu::showSide()
{
    for (int j = 1; j < side.get_sx(); j++)
    {
        for (int i = 1; i < side.get_sy(); i++)
        {
            screen[j + BottomPlank][i + SidePlank] = side.get_screen()[j][i];
        }
    }
}

void GMGameMenu::mapping(int& position, const int num)
{
    int n = num;
    int max = Res.getMax();
    int i = Res.getSpace() / 2;
    if (!n)
    {
        CharOut(n, Res.getInit_y(), position + i);
        while (max)
        {
            i--;
            max /= 10;
            CharOut(' ', Res.getInit_y(), position + i);
        }
    }
    else
    {
        while (max != 0)
        {
            {
                if (n)
                {
                    CharOut(n % 10, Res.getInit_y(), position + i);
                    n = n / 10;
                }
                else
                {
                    CharOut(' ', Res.getInit_y(), position + i);
                }
                i--;
                max = max / 10;
            }
        }
    }
}

void GMGameMenu::mapResources()
{
    int position = Res.getInit_x() + unsigned(strlen(texts_1::wood));
    int num = Res.getWood();
    mapping(position, num);

    position += Res.getSpace() + unsigned(strlen(texts_1::seeds));
    num = Res.getSeeds();
    mapping(position, num);

    position += Res.getSpace() + unsigned(strlen(texts_1::food));
    num = Res.getFood();
    mapping(position, num);

    position += Res.getSpace() + unsigned(strlen(texts_1::money));
    num = Res.getMoney();
    mapping(position, num);

    int Position = position + Res.getSpace() + unsigned(strlen(texts_1::farmers));
    int i = Res.getSpace() / 2;
    for (int j = 0; j < SidePlank - Position; j++)
    {
        CharOut(' ', Res.getInit_y(), Position + j);
    }
    position += Res.getSpace() + unsigned(strlen(texts_1::farmers));
    num = farmers.getcount();
    do
    {
        int n = num % 10;
        CharOut(n, Res.getInit_y(), position + i);
        num = num / 10;
        i--;
        CharOut('/', Res.getInit_y(), position + i);
    } while (num != 0);
    num = farmers.freeFarmers();
    do
    {
        i--;
        int n = num % 10;
        CharOut(n, Res.getInit_y(), position + i);
        num = num / 10;
    } while (num != 0);

}

void GMGameMenu::seeder()
{
    int l1 = x1;
    int l2 = x2;
    int h1 = y1;
    int h2 = y2;

    if (l1 > l2)
    {
        l1 = x2;
        l2 = x1;
    }
    if (h1 > h2)
    {
        h1 = y2;
        h2 = y1;
    }

    for (int j = h1; j < h2 + 1; j++)
    {
        for (int i = l1; i < l2 + 1; i++)
        {
            if (screen[j][i] == ' ')
            {
                CharOut('.', j, i);
            }
        }
    }

}

void GMGameMenu::setPlants(enum plants p)
{
    plant = p;
}

void GMGameMenu::showDialog()
{
    for (int j = 1; j < Dial.getPx() - 1; j++)
    {
        for (int i = 1; i < Dial.getPy() - 1; i++)
        {
            screen[BottomPlank + j][i] = Dial.getBox()[j][i];
        }
    }
}

GMGameMenu::~GMGameMenu()
{
}
