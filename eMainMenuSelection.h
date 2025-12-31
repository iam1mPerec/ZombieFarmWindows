#pragma once

enum class eMainMenuSelection
{
    NewGame = 1,
    Continue = 2,
    Exit = 3
};

inline eMainMenuSelection& operator++(eMainMenuSelection& selection)
{
    selection = static_cast<eMainMenuSelection>(static_cast<int>(selection) + 1);
    return selection;
}

inline eMainMenuSelection& operator--(eMainMenuSelection& selection)
{
    selection = static_cast<eMainMenuSelection>(static_cast<int>(selection) - 1);
    return selection;
}