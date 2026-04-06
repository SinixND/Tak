#include "History.h"

#include "ActionTypeId.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

History newHistory( void )
{
    History history = {
        .lastRecordIdx = -1,
        .redoCount = 0,
    };

    for ( int idx = 0; idx < HISTORY_SIZE; ++idx )
    {
        // history.actions[idx] = newHistoryRecord();
    }

    return history;
}

void recordActionPlacement(
    History* const pHistory,
    PlayerId const playerId,
    int const squareIdx,
    StoneType const stoneType
)
{
    //* Increase index
    ++pHistory->lastRecordIdx;

    //* Might never trigger
    assert(
        pHistory->lastRecordIdx < HISTORY_SIZE
        && "History size exceeded"
    );

    //* Reset redo count
    pHistory->redoCount = 0;

    //* Push playerAction
    pHistory->records[pHistory->lastRecordIdx]
        = (HistoryRecord){
            .actionType = ACTION_TYPE_PLACE,
            .playerId = playerId,
            .squareIdx = squareIdx,
            .stoneType = stoneType,
        };
}

void recordActionLift(
    History* const pHistory,
    int const squareIdx
)
{
    //* Increase index
    ++pHistory->lastRecordIdx;

    //* Might never trigger
    assert(
        pHistory->lastRecordIdx < HISTORY_SIZE
        && "History size exceeded"
    );

    //* Reset redo count
    pHistory->redoCount = 0;

    //* Push playerAction
    pHistory->records[pHistory->lastRecordIdx]
        = (HistoryRecord){
            .actionType = ACTION_TYPE_LIFT,
            .squareIdx = squareIdx,
        };
}

void recordActionDrop(
    History* const pHistory,
    int const squareIdx,
    bool const flattened
)
{
    //* Increase index
    ++pHistory->lastRecordIdx;

    //* Might never trigger
    assert(
        pHistory->lastRecordIdx < HISTORY_SIZE
        && "History size exceeded"
    );

    //* Reset redo count
    pHistory->redoCount = 0;

    //* Push playerAction
    pHistory->records[pHistory->lastRecordIdx]
        = (HistoryRecord){
            .actionType = ACTION_TYPE_DROP,
            .squareIdx = squareIdx,
            .flattened = flattened,
        };
}

void undoHistory( History* const pHistory )
{
    assert(
        pHistory->lastRecordIdx >= 0
        && "Nothing to be undone"
    );

    --pHistory->lastRecordIdx;
    ++pHistory->redoCount;
}

void redoHistory( History* const pHistory )
{
    assert(
        pHistory->redoCount > 0
        && "Nothing to be redone"
    );

    ++pHistory->lastRecordIdx;
    --pHistory->redoCount;
}
