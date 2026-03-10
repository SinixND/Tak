#include "HistorySystem.h"

#include "DirectionId.h"
#include "GameConstants.h"
#include "PlayerAction.h"
#include <assert.h>

void recordPlacementAction(
    History* const pHistory,
    StoneType const stoneType,
    FileId const fileX,
    RankId const rankY
)
{
    //* Increase index
    ++pHistory->lastActionIdx;

    //* Might never trigger
    assert(
        pHistory->lastActionIdx < HISTORY_SIZE
        && "Nothing to be undone"
    );

    //* Reset redo count
    pHistory->redoCount = 0;

    //* Push pPlayerAction
    pHistory->actions[pHistory->lastActionIdx] = (PlayerAction){
        .count = 0,
        .stoneType = stoneType,
        .fileX = fileX,
        .rankY = rankY,
        .direction = DIR_NONE,
        .flattend = 0,
        .drops = { 0 }
    };
}

void undoHistory( History* const pHistory )
{
    assert(
        pHistory->lastActionIdx > 0
        && "Nothing to be undone"
    );

    --pHistory->lastActionIdx;
    ++pHistory->redoCount;
}

void redoHistory( History* const pHistory )
{
    assert(
        pHistory->redoCount > 0
        && "Nothing to be redone"
    );

    ++pHistory->lastActionIdx;
    --pHistory->redoCount;
}
