#pragma once
#include "GMBase.h"
#include "eMainMenuSelection.h"

class GMMainMenu : public GMBase
{
private:
    bool start;
protected:
    bool loading;
    const int x;
    const int y;
	eMainMenuSelection selection;
public:
    GMMainMenu(class engine* engine, char** screen);
    void selector(const int position, const char* name);
	void midler(const int position, const char* name);
    void frame();
    void controlSignal(eControls controls) override;
    void submit() override;
    void up() override;
	void down() override;
	void Draw(float fElapsedTime) override;
};