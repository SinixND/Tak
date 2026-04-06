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
    FileId const fileX,
    RankId const rankY,
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
            .fileX = fileX,
            .rankY = rankY,
            .stoneType = stoneType,
        };
}

void recordActionLift(
    History* const pHistory,
    FileId const fileX,
    RankId const rankY
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
            .fileX = fileX,
            .rankY = rankY,
        };
}

void recordActionDrop(
    History* const pHistory,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY,
    StoneType const stoneType,
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
            .playerId = playerId,
            .fileX = fileX,
            .rankY = rankY,
            .stoneType = stoneType,
            .stoneCount = 1,
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
