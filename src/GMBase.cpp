#include "GMBase.h"
#include "screen.h"

GMBase::GMBase(engine* engine, char** screen) :
    m_inProgress(true),
    m_engine(engine),
	screen(screen)
{
	clear();
}

bool GMBase::inProgress() const {
    return m_inProgress;
}

void GMBase::showQuote(string quote)
{
}

void GMBase::clear()
{
	for (int i = 1; i < x - 1; i++)
	{
		for (int j = 1; j < y - 1; j++)
		{
			screen[i][j] = ' ';
		}
	}
}

void GMBase::print()
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (screen[i][j] == 30)
			{
				m_engine->Draw(j, i, L'☀'); 
			}
			else if (screen[i][j] == 31)
			{
				m_engine->Draw(j, i, L'⚇');
			}
			else if (screen[i][j] == '#')
			{
				m_engine->Draw(j, i, L'√');
			}
			else if (screen[i][j] == '$')
			{
				m_engine->Draw(j, i, L'❦');
			}
			else if (screen[i][j] == '^')
			{
				m_engine->Draw(j, i, L'X');
			}
			else if (screen[i][j] == 9)
			{
				m_engine->Draw(j, i, L'☽');
			}
			else if (screen[i][j] == 1)
			{
				m_engine->Draw(j, i, L'✙');
			}
			else if (screen[i][j] == 2)
			{
				m_engine->Draw(j, i, L'◕');
			}
			else if (screen[i][j] == 3)
			{
				m_engine->Draw(j, i, L'☩');
			}
			else if (screen[i][j] == 4)
			{
				m_engine->Draw(j, i, L'◣');
			}
			else if (screen[i][j] == 5)
			{
				m_engine->Draw(j, i, L'◢');
			}
			else if (screen[i][j] == 6)
			{
				m_engine->Draw(j, i, L'▫');
			}
			else if (screen[i][j] == 7)
			{
				m_engine->Draw(j, i, L'●');
			}
			else if (screen[i][j] == 8)
			{
				m_engine->Draw(j, i, L'◼');
			}
			else
			{
				m_engine->Draw(j, i, wchar_t(screen[i][j]));
			}
		}
	}
}

