#include <iostream>
#include "GMMainMenu.h"
#include "olcConsoleGameEngine.h"
#include "keys.h"
#include "GMGameMenu.h"
#include "texts_1.h"
#include "Abilities.h"
#include <windows.h>
#include <conio.h>
using namespace std;

GMMainMenu::GMMainMenu(engine* engine, char** screen)
    : GMBase(engine, screen),
      start(false),
      loading(false),
      x(engine::consoleHeight),
      y(engine::consoleWidth),
      selection(eMainMenuSelection::NewGame)
{
    frame();
}

void GMMainMenu::midler(const int position, const char* name)
{
	for (int i = 0; i < strlen(name); i++)
	{
		screen[position][i + (y / 2 - unsigned(strlen(name)) / 2)] = name[i];
	}

}

void GMMainMenu::frame()
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			screen[i][j] = ' ';
		}
	}

	for (int i = 0 + 1; i < y - 1; i++)
	{
		screen[0][i] = '_';
	}

	for (int i = 0; i < y; i++)
	{
		screen[x - 1][i] = '_';
	}


	for (int i = 0 + 1; i < x; i++)
	{
		screen[i][0] = '|';
	}

	for (int i = 0 + 1; i < x; i++)
	{
		screen[i][y - 1] = '|';
	}

}

void GMMainMenu::selector(const int position, const char* name)
{
	screen[position][(y / 2 - unsigned(strlen(name)) / 2) - 1] = '<';

	if (strlen(name) % 2 == 1)
	{
		screen[position][(y / 2 + unsigned(strlen(name)) / 2) + 1] = '>';
	}
	else
	{
		screen[position][(y / 2 + unsigned(strlen(name)) / 2)] = '>';
	}
}

void GMMainMenu::Update(float fElapsedTime)
{
	switch (this->selection)
	{
	case eMainMenuSelection::NewGame:
		selector(25, texts_1::game);
		break;
	case eMainMenuSelection::Continue:
		selector(27, texts_1::load);
		break;
	case eMainMenuSelection::Exit:
		selector(29, texts_1::quit);
		break;
	}
	midler(10, texts_1::welcome);
	midler(11, texts_1::name);
	midler(25, texts_1::game);
	midler(27, texts_1::load);
	midler(29, texts_1::quit);
	for (int i = 0; i < strlen(texts_1::credits); i++)
	{
		screen[x - 2][i + y - strlen(texts_1::credits) - 2] = texts_1::credits[i];
	}
	print();
	clear();
}

void GMMainMenu::controlSignal(eControls controls)
{
	switch (controls) {
	case eControls::UP:
		up();
		break;
	case eControls::DOWN:
		down();
		break;
	case eControls::SUBMIT:
		submit();
		break;
	default:
		break;
	}
}

void GMMainMenu::submit()
{
	switch (this->selection)
	{
	case eMainMenuSelection::NewGame:
		clear();
		m_engine->setGameMode(new GMGameMenu(false, this->m_engine, screen));
		break;
	case eMainMenuSelection::Continue:
		clear();
		m_engine->setGameMode(new GMGameMenu(true, this->m_engine, screen));
		break;
	case eMainMenuSelection::Exit:
		exit(0);
		break;
	}
}

void GMMainMenu::up()
{
	--selection;

	if (selection < eMainMenuSelection::NewGame)
	{
		selection = eMainMenuSelection::Exit;
	}
}

void GMMainMenu::down()
{
	++selection;

	if (selection > eMainMenuSelection::Exit)
	{
		selection = eMainMenuSelection::NewGame;
	}
}
