#include "engine.h"
#include "eColors.h"
#include "GMMainMenu.h"

const int engine::consoleHeight = 52;
const int engine::consoleWidth = 130;

engine::engine() :
    m_mode(nullptr),
	locked(false)
{
}
void engine::begin() {
    char ** screen = new char* [consoleHeight];
    for (int i = 0; i < consoleHeight; i++)
    {
        screen[i] = new char[consoleWidth];
    }
    m_mode = new GMMainMenu(this, screen);
    ConstructConsole(consoleWidth, consoleHeight, 12, 14);
    Start();
}

void engine::startAnimation(int frames, float seconds_per_frame, std::function<void(int, int)> draw_func, std::function<void()> on_complete)
{
    locked = true;
    currentAnimation.currentFrame = 0;
    currentAnimation.totalFrames = frames;
    currentAnimation.frameDuration = seconds_per_frame;
    currentAnimation.accumulator = 0.0f;
    currentAnimation.drawFrame = draw_func;
	currentAnimation.onComplete = on_complete;
}

void engine::pause(float seconds, std::function<void()> onComplete)
{
	startAnimation(1, seconds, [](int, int) {}, onComplete);
}

void engine::playAnimation(float fElapseTime)
{
    if (currentAnimation.currentFrame == -1) {
        locked = false;
        return;
    }
    currentAnimation.accumulator += fElapseTime;
    
    if (currentAnimation.accumulator >= currentAnimation.frameDuration) {
        currentAnimation.accumulator = 0;
        currentAnimation.currentFrame++;
        currentAnimation.drawFrame(currentAnimation.currentFrame, currentAnimation.totalFrames);
    }

    if (currentAnimation.isComplete()) {
        stopAnimation();
        if (currentAnimation.onComplete != nullptr) currentAnimation.onComplete();
    }
}

void engine::stopAnimation()
{
	currentAnimation.currentFrame = -1;
    locked = false;
}

void engine::setOnKeyPressed(std::function<void()> action)
{
    onKeyPressed = action;
}

void engine::setGameMode(GMBase* newGameMode) {
    if (m_mode) {
        delete m_mode;
    }
    m_mode = newGameMode;
}

bool engine::OnUserCreate() {
    return true;
}

bool engine::isLocked() const
{
    return locked; 
}

void engine::signalKeyPressed()
{
    if (onKeyPressed != nullptr && !locked) {
        onKeyPressed();
        onKeyPressed = nullptr;
    }
}

bool engine::OnUserUpdate(float fElapsedTime) {
    //MARK: - Handle input
    if (!locked) {
        if (m_keys[VK_RETURN].bPressed || m_keys[L'F'].bPressed) {
            signalKeyPressed();
            m_mode->controlSignal(eControls::SUBMIT);
        }
        if (m_keys[VK_ESCAPE].bPressed || m_keys[L'E'].bPressed) {
            signalKeyPressed();
            m_mode->controlSignal(eControls::QUIT);
        }
        if (m_keys[VK_UP].bPressed || m_keys[L'W'].bPressed) {
            signalKeyPressed();
            m_mode->controlSignal(eControls::UP);
        }
        if (m_keys[VK_DOWN].bPressed || m_keys[L'S'].bPressed) {
            signalKeyPressed();
            m_mode->controlSignal(eControls::DOWN);
        }
        if (m_keys[VK_LEFT].bPressed || m_keys[L'A'].bPressed) {
            signalKeyPressed();
            m_mode->controlSignal(eControls::LEFT);
        }
        if (m_keys[VK_RIGHT].bPressed || m_keys[L'D'].bPressed) {
            signalKeyPressed();
            m_mode->controlSignal(eControls::RIGHT);
        }
        if (m_keys[L'I'].bPressed) {
            signalKeyPressed();
            m_mode->controlSignal(eControls::INFO);
        }
        if (m_keys[L'C'].bPressed) {
            signalKeyPressed();
            m_mode->controlSignal(eControls::CLEAR);
        }
        if (m_keys[L'L'].bPressed) {
            signalKeyPressed();
            m_mode->controlSignal(eControls::SELL);
        }
    }
    

	//MARK: - Play animation
    playAnimation(fElapsedTime);

    //MARK: - Update and Render
    m_mode->Update(fElapsedTime);
    
    return m_mode->inProgress();
}

engine::~engine() {
    delete m_mode;
}