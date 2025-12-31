#include "engine.h"
#include "eColors.h"
#include "GMMainMenu.h"

const int engine::consoleHeight = 52;
const int engine::consoleWidth = 130;

engine::engine() :
    m_mode(nullptr)
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

void engine::setGameMode(GMBase* newGameMode) {
    if (m_mode) {
        delete m_mode;
    }
    m_mode = newGameMode;
}

bool engine::OnUserCreate() {
    return true;
}

bool engine::OnUserUpdate(float fElapsedTime) {
    //MARK: - Handle input
    if (m_keys[VK_ACCEPT].bPressed || m_keys[L'F'].bPressed) m_mode->controlSignal(eControls::SUBMIT);
    if (m_keys[VK_ESCAPE].bPressed || m_keys[L'E'].bPressed) m_mode->controlSignal(eControls::QUIT);
    if (m_keys[VK_UP].bPressed || m_keys[L'W'].bPressed) m_mode->controlSignal(eControls::UP);
    if (m_keys[VK_DOWN].bPressed || m_keys[L'S'].bPressed) m_mode->controlSignal(eControls::DOWN);
    if (m_keys[VK_LEFT].bPressed || m_keys[L'A'].bPressed) m_mode->controlSignal(eControls::LEFT);
    if (m_keys[VK_RIGHT].bPressed || m_keys[L'D'].bPressed) m_mode->controlSignal(eControls::RIGHT);
    if (m_keys[L'I'].bPressed) m_mode->controlSignal(eControls::INFO);
    if (m_keys[L'C'].bPressed) m_mode->controlSignal(eControls::CLEAR);
	if (m_keys[L'L'].bPressed) m_mode->controlSignal(eControls::SELL);
    
    //MARK: - Update state

    //MARK: - Render
    m_mode->Draw(fElapsedTime);
    
    return m_mode->inProgress();
}

engine::~engine() {
    delete m_mode;
}