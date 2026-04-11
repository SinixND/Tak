#include "Engine.h"

#include "Command.h"
#include "Event.h"
#include "Game.h"
#include "PositionSystem.h"
#include <assert.h>

Engine newEngine( void )
{
    return (Engine){
        .event = newEvent(),
        .command = newCommand(),
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

void executeEvent(
    Game* const pGame,
    Event const* const pEvent
)
{
    assert(
        pGame
        && "Pointer is nullptr"
    );

    assert(
        pEvent
        && "Pointer is nullptr"
    );

    switch ( pEvent->actionType )
    {
        default:
        {
            assert( !"No action type set" );

            return;
        }

        case ACTION_TYPE_PLACE:
        {
            placeStone(
                pGame,
                pEvent->playerId,
                pEvent->squareIdx,
                pEvent->stoneType
            );

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            liftStack(
                pGame,
                pEvent->squareIdx
            );

            return;
        }

        case ACTION_TYPE_DROP:
        {
            for ( int i = 0; i < pEvent->dropCount; ++i )
            {
                dropStone(
                    pGame,
                    pEvent->squareIdx
                );
            }

            return;
        }
    }
}
