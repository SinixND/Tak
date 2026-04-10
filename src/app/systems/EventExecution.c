#include "EventExecution.h"

#include "App.h"
#include <assert.h>

void executeEvent( App* const pApp )
{
    Event const* const pEvent = &pApp->event;
    Game* const pGame = &pApp->game;

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

