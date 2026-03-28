#include "HistorySystem.h"

#include "ActionTypeId.h"
#include "GameConstants.h"
#include "History.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

History newHistory( void )
{
    History history = {
        .lastActionIdx = -1,
        .redoCount = 0,
    };

    for ( int idx = 0; idx < HISTORY_SIZE; ++idx )
    {
        // history.actions[idx] = newPlayerAction();
    }

    return history;
}

void recordPlacementAction(
    History* const pHistory,
    PlayerId const playerId,
    int const squareIdx,
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
            .actionType = ACTION_TYPE_PLACE,
            .playerId = playerId,
            .squareIdx = squareIdx,
            .stoneType = stoneType,
            .stoneCount = 0,
            .flattened = false,
        };
}

void recordLiftAction(
    History* const pHistory,
    int const squareIdx,
    int const topStoneIdx,
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
            .actionType = ACTION_TYPE_LIFT,
            .squareIdx = squareIdx,
            .topStoneIdx = topStoneIdx,
            .stoneType = stoneType,
            .stoneCount = stoneCount,
            .flattened = false,
        };
}

void recordDropAction(
    History* const pHistory,
    PlayerId const playerId,
    int const squareIdx,
    StoneType const stoneType,
    bool const flattened
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
            .actionType = ACTION_TYPE_DROP,
            .playerId = playerId,
            .squareIdx = squareIdx,
            .stoneType = stoneType,
            .stoneCount = 1,
            .flattened = flattened,
        };
}

void undoHistory( History* const pHistory )
{
    assert(
        pHistory->lastActionIdx >= 0
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
