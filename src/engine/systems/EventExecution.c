#include "EventExecution.h"

#include "Event.h"
#include "Game.h"
#include <assert.h>

void executeEvent(

    Game* const pGame,
    Event const* const pEvent
)
{
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

