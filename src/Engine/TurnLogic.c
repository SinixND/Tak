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
    validateEventPlace(
        &pApp->gameEvent,
        &pApp->game
    );

    placeStone(
        &pApp->game,
        pApp->gameEvent.playerId,
        pApp->gameEvent.fileX,
        pApp->gameEvent.rankY,
        pApp->gameEvent.stoneType
    );

    recordActionPlacement(
        &pApp->history,
        pApp->gameEvent.playerId,
        pApp->gameEvent.fileX,
        pApp->gameEvent.rankY,
        pApp->gameEvent.stoneType
    );

    return;
}

void applyEventLift( App* const pApp )
{
    validateEventLift(
        &pApp->gameEvent,
        &pApp->game
    );

    liftStack(
        &pApp->game,
        pApp->gameEvent.fileX,
        pApp->gameEvent.rankY
    );

    recordActionLift(
        &pApp->history,
        pApp->gameEvent.fileX,
        pApp->gameEvent.rankY
    );

    return;
}

void applyEventDrop( App* const pApp )
{
    int const squareIdx
        = positionToSquare(
            pApp->gameEvent.fileX,
            pApp->gameEvent.rankY,
            pApp->game.board.width
        );

    StoneType const captiveStoneType = pApp->game.board.types[squareIdx];

    StoneType const droppedStoneType
        = ( pApp->game.stackBuffer.stoneCount > 1 )
              ? STONE_TYPE_FLAT
              : pApp->game.stackBuffer.stoneType;

    bool const flattened = ( droppedStoneType == STONE_TYPE_CAP )
                           && ( captiveStoneType == STONE_TYPE_STANDING );

    validateEventDrop(
        &pApp->gameEvent,
        &pApp->game
    );

    for ( int i = 0; i < pApp->gameEvent.dropCount; ++i )
    {
        dropStone(
            &pApp->game,
            pApp->gameEvent.fileX,
            pApp->gameEvent.rankY
        );

        recordActionDrop(
            &pApp->history,
            pApp->gameEvent.playerId,
            pApp->gameEvent.fileX,
            pApp->gameEvent.rankY,
            pApp->gameEvent.stoneType,
            flattened
        );
    }

    return;
}

