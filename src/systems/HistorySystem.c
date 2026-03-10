#include "HistorySystem.h"
#include "DirectionId.h"
#include "GameConstants.h"
#include "PlayerAction.h"

void recordPlacementAction(
    History* const pHistory,
    StoneType const stoneType,
    FileId const fileX,
    RankId const rankY
)
{
    //* Increase counter
    stepForward( pHistory );

    //* Push pPlayerAction
    pHistory->undoActions[pHistory->lastActionIdx % HISTORY_SIZE] = (PlayerAction){
        .count = 0,
        .stoneType = stoneType,
        .fileX = fileX,
        .rankY = rankY,
        .direction = DIR_NONE,
        .flattend = 0,
        .drops = { 0 }
    };
}

void stepBack( History* const pHistory )
{
    --pHistory->lastActionIdx;

    //* Ensure lastActionIdx is below HISTORY_SIZE
    pHistory->lastActionIdx = ( pHistory->lastActionIdx + HISTORY_SIZE ) % HISTORY_SIZE;
}

void stepForward( History* const pHistory )
{
    ++pHistory->lastActionIdx;

    //* Ensure lastActionIdx is below HISTORY_SIZE
    pHistory->lastActionIdx = ( pHistory->lastActionIdx + HISTORY_SIZE ) % HISTORY_SIZE;
}
