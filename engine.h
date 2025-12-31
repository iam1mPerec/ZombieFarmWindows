#define WIN32_LEAN_AND_MEAN
#include "olcConsoleGameEngine.h"
#pragma once
class engine : public olcConsoleGameEngineOOP{
    //implementing gameMod ref as a part of the Strategy design pattern
    //gameMode will tell the engine what to draw where and when
    //the engine would handle drawing and keyboard events
    class GMBase* m_mode;
public:
    static const int consoleHeight;
    static const int consoleWidth;

    engine();
    void begin();
    void setGameMode(class GMBase* newGameMode);
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    ~engine();
};
