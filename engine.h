#define WIN32_LEAN_AND_MEAN
#include "olcConsoleGameEngine.h"
#include <functional>
#pragma once

struct Animation {
    int currentFrame = -1;
    int totalFrames = 0;
    float frameDuration = 0.0f;
    float accumulator = 0.0f;
    std::function<void(int)> drawFrame;
    std::function<void()> onComplete;

    bool isComplete() const {
        return currentFrame >= totalFrames;
	}
};

class engine : public olcConsoleGameEngineOOP{
    //implementing gameMod ref as a part of the Strategy design pattern
    //gameMode will tell the engine what to draw where and when
    //the engine would handle drawing and keyboard events
    class GMBase* m_mode;
	Animation currentAnimation;
	std::function<void()> onKeyPressed;
public:
    static const int consoleHeight;
    static const int consoleWidth;

    engine();
    void begin();
    void startAnimation(int frames, float secondsPerFrame, std::function<void(int)> drawFunc, std::function<void()> onComplete = nullptr);
    void pause(float seconds, std::function<void()> onComplete);
    void playAnimation(float fElapseTime);
    void stopAnimation();
    void setOnKeyPressed(std::function<void()>);
    void setGameMode(class GMBase* newGameMode);
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    ~engine();
};
