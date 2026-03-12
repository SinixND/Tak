#include "HistorySystem.h"

#include "GameConstants.h"
#include "PlayerAction.h"
#include "PlayerId.h"
#include <assert.h>
#include <stdbool.h>

void recordPlacementAction(
    History* const pHistory,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY,
    StoneType const stoneType
)
{
    //* Increase index
    ++pHistory->lastActionIdx;

    //* Might never trigger
    assert(
        pHistory->lastActionIdx < HISTORY_SIZE
        && "History size exceeded"
    );

    //* Reset redo count
    pHistory->redoCount = 0;

    //* Push playerAction
    pHistory->actions[pHistory->lastActionIdx]
        = (PlayerAction){
            .playerId = playerId,
            .fileX = fileX,
            .rankY = rankY,
            .stoneType = stoneType,
            .stoneCount = 0,
            .flattened = false,
        };
}

void recordPickUpAction(
    History* const pHistory,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY,
    StoneType const stoneType,
    int const stoneCount
)
{
    //* Increase index
    ++pHistory->lastActionIdx;

    //* Might never trigger
    assert(
        pHistory->lastActionIdx < HISTORY_SIZE
        && "History size exceeded"
    );

    //* Reset redo count
    pHistory->redoCount = 0;

    //* Push playerAction
    pHistory->actions[pHistory->lastActionIdx]
        = (PlayerAction){
            .playerId = playerId,
            .fileX = fileX,
            .rankY = rankY,
            .stoneType = stoneType,
            .stoneCount = stoneCount,
            .flattened = false,
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
