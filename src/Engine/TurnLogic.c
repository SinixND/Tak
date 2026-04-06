#include "TurnLogic.h"

#include "App.h"
#include "GameEventValidation.h"
#include "History.h"
#include "PositionSystem.h"
#include <assert.h>

void executeTurn( App* const pApp )
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
    GameEvent const* const pEvent = &pApp->gameEvent;

    validateEventPlace(
        pEvent,
        &pApp->game
    );

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

    recordActionPlacement(
        &pApp->history,
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
    GameEvent const* const pEvent = &pApp->gameEvent;

    validateEventLift(
        pEvent,
        &pApp->game
    );

    liftStack(
        &pApp->game,
        positionToSquare(
            pEvent->fileX,
            pEvent->rankY,
            pApp->game.board.width
        )
    );

    recordActionLift(
        &pApp->history,
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
    GameEvent const* const pEvent = &pApp->gameEvent;
    Game const* const pGame = &pApp->game;

    int const squareIdx
        = positionToSquare(
            pEvent->fileX,
            pEvent->rankY,
            pGame->board.width
        );

    StoneType const captiveStoneType = pGame->board.stackTypes[squareIdx];

    StoneType const droppedStoneType
        = ( pGame->stackBuffer.stoneCount > 1 )
              ? STONE_TYPE_FLAT
              : pGame->stackBuffer.stoneType;

    bool const flattened = ( droppedStoneType == STONE_TYPE_CAP )
                           && ( captiveStoneType == STONE_TYPE_STANDING );

    validateEventDrop(
        pEvent,
        pGame
    );

    for ( int i = 0; i < pEvent->dropCount; ++i )
    {
        dropStone(
            &pApp->game,
            positionToSquare(
                pEvent->fileX,
                pEvent->rankY,
                pGame->board.width
            )
        );

        recordActionDrop(
            &pApp->history,
            positionToSquare(
                pEvent->fileX,
                pEvent->rankY,
                pGame->board.width
            ),
            flattened
        );
    }

    return;
}

