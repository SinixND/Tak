#include "EventExecution.h"

#include "App.h"
#include "PositionSystem.h"
#include <assert.h>

void executeEvent( App* const pApp )
{
    switch ( pApp->gameEvent.actionType )
    {
        default:
        {
            assert( !"No action type set" );

            return;
        }

        case ACTION_TYPE_PLACE:
        {
            applyEventPlace( pApp );

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            applyEventLift( pApp );

            return;
        }

        case ACTION_TYPE_DROP:
        {
            applyEventDrop( pApp );

            return;
        }
    }
}

void applyEventPlace( App* const pApp )
{
    Event const* const pEvent = &pApp->gameEvent;

    placeStone(
        &pApp->game,
        pEvent->playerId,
        positionToSquare(
            pEvent->fileX,
            pEvent->rankY,
            pApp->game.board.width
        ),
        pEvent->stoneType
    );

    return;
}

void applyEventLift( App* const pApp )
{
    Event const* const pEvent = &pApp->gameEvent;

    liftStack(
        &pApp->game,
        positionToSquare(
            pEvent->fileX,
            pEvent->rankY,
            pApp->game.board.width
        )
    );

    return;
}

void applyEventDrop( App* const pApp )
{
    Game* const pGame = &pApp->game;
    Event const* const pEvent = &pApp->gameEvent;

    for ( int i = 0; i < pEvent->dropCount; ++i )
    {
        dropStone(
            pGame,
            positionToSquare(
                pEvent->fileX,
                pEvent->rankY,
                pGame->board.width
            )
        );
    }

    return;
}

