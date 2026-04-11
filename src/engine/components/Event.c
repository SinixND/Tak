#include "Event.h"

#include "PositionSystem.h"
#include <assert.h>
#include <stdbool.h>

Event newEvent( void )
{
    return (Event){
        .playerId = PLAYER_NONE,
        .actionType = ACTION_TYPE_NONE,
        .stoneType = STONE_TYPE_NONE,
        .squareIdx = -1,
        .dropCount = -1,
    };
}

void buildEvent(
    Event* const pEvent,
    Command const* const pCommand,
    int const boardSize
)
{
    assert(
        pEvent
        && "Pointer is nullptr"
    );

    assert(
        pCommand
        && "Pointer is nullptr"
    );

    pEvent->actionType = pCommand->actionType;
    pEvent->playerId = pCommand->playerId;
    pEvent->stoneType = pCommand->stoneType;
    pEvent->squareIdx
        = ( ( pCommand->fileX + pCommand->rankY ) < 0 )
              ? -1
              : positionToSquare(
                    pCommand->fileX,
                    pCommand->rankY,
                    boardSize
                );
    pEvent->dropCount = pCommand->dropCounts[pCommand->drops - 1];
}
