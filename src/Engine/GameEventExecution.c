#include "GameEventExecution.h"

#include "Game.h"
#include "GameEvent.h"
#include <assert.h>

void applyEvent(
    Game* const pGame,
    GameEvent const* const pEvent
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
            applyEventPlace(
                pGame,
                pEvent
            );

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            applyEventLift(
                pGame,
                pEvent
            );
            return;
        }

        case ACTION_TYPE_DROP:
        {
            applyEventDrop(
                pGame,
                pEvent
            );

            return;
        }
    }
}

void applyEventPlace(
    Game* const pGame,
    GameEvent const* const pEvent
)
{
    placeStone(
        pGame,
        pEvent->playerId,
        pEvent->fileX,
        pEvent->rankY,
        pEvent->stoneType
    );

    return;
}

void applyEventLift(
    Game* const pGame,
    GameEvent const* const pEvent
)
{
    liftStack(
        pGame,
        pEvent->fileX,
        pEvent->rankY
    );

    return;
}

void applyEventDrop(
    Game* const pGame,
    GameEvent const* const pEvent
)
{
    for ( int i = 0; i < pEvent->dropCount; ++i )
    {
        dropStone(
            pGame,
            pEvent->fileX,
            pEvent->rankY
        );
    }

    return;
}

