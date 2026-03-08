#include "HistorySystem.h"

void addAction(
    History* const pHistory,
    PlayerAction const pPlayerAction
)
{
    //* Push pPlayerAction
    pHistory->undoActions[pHistory->undoCount] = pPlayerAction;

    //* Increase counter
    ++pHistory->undoCount;
}
