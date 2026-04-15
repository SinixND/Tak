#include "EventBuilding.h"

#include "Command.h"
#include "Event.h"
#include "Position.h"
#include <assert.h>

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
