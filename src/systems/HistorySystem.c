#include "HistorySystem.h"
#include "GameConstants.h"

void recordAction(
    History* const pHistory,
    PlayerAction const pPlayerAction
)
{
    //* Increase counter
    ++pHistory->lastActionIdx;

    //* Push pPlayerAction
    pHistory->undoActions[pHistory->lastActionIdx % HISTORY_SIZE] = pPlayerAction;
}

void undoLastAction( History* const pHistory )
{
    --pHistory->lastActionIdx;

    //* Ensure lastActionIdx is below HISTORY_SIZE
    pHistory->lastActionIdx = ( pHistory->lastActionIdx + HISTORY_SIZE ) % HISTORY_SIZE;
}

void redoNextAction( History* const pHistory )
{
    ++pHistory->lastActionIdx;

    //* Ensure lastActionIdx is below HISTORY_SIZE
    pHistory->lastActionIdx = ( pHistory->lastActionIdx + HISTORY_SIZE ) % HISTORY_SIZE;
}
