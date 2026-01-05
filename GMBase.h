#pragma once
#include "engine.h"
#include "eControls.h"

class GMBase {
protected:
    bool m_inProgress;
    class engine* m_engine;
    char** screen;
public:
    GMBase(engine* engine, char** screen);
    virtual void Update(float fElapsedTime) = 0;
    bool inProgress() const;

    virtual void submit() {};
    virtual void quit() {};
    virtual void up() {};
    virtual void down() {};
    virtual void left() {};
    virtual void right() {};
    virtual void showQuote(string quote);
	virtual void clear();
	virtual void print();
    virtual void controlSignal(eControls controls) {};
};
