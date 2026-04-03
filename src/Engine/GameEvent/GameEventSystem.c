#include "GameEventSystem.h"

#include "ActionTypeId.h"
#include "GameEvent.h"
#include "PositionSystem.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

GameEvent newGameEvent( void )
{
    return (GameEvent){
        .playerId = PLAYER_NONE,
        .actionType = ACTION_TYPE_NONE,
        .stoneType = STONE_TYPE_NONE,
        .fileX = FILE_NONE,
        .rankY = RANK_NONE,
        .dropCount = 0,
    };
}

bool validateEvent(
    GameEvent const* const pEvent,
    Game const* const pGame
)
{
    switch ( pEvent->actionType )
    {
        default:
            return false;

        case ACTION_TYPE_PLACE:
        {
            return validateEventPlace(
                pEvent,
                pGame
            );
        }

        case ACTION_TYPE_LIFT:
        {
            return validateEventLift(
                pEvent,
                pGame
            );
        }

        case ACTION_TYPE_DROP:
        {
            return validateEventDrop(
                pEvent,
                pGame
            );
        }
    }
}

bool validateEventPlace(
    GameEvent const* const pEvent,
    Game const* const pGame
)
{
    //* Stone type available
    if ( !isStoneTypeAvailable(
             pEvent,
             &pGame->reserves
         ) )
    {
        return false;
    }

    //* FileX on board
    if ( !isFileXOnBoard(
             pEvent,
             pGame->board.width
         ) )
    {
        return false;
    }

    //* RankY on board
    if ( !isRankYOnBoard(
             pEvent,
             pGame->board.width
         ) )
    {
        return false;
    }

    //* Can only place on empty square
    if ( !isSquareEmpty(
             pEvent,
             &pGame->board
         ) )
    {
        return false;
    }

    return true;
}

bool validateEventLift(
    GameEvent const* const pEvent,
    Game const* const pGame
)
{
    //* FileX on board
    if ( !isFileXOnBoard(
             pEvent,
             pGame->board.width
         ) )
    {
        return false;
    }

    //* RankY on board
    if ( !isRankYOnBoard(
             pEvent,
             pGame->board.width
         ) )
    {
        return false;
    }

    //* Must lift at least one stone
    if ( isSquareEmpty(
             pEvent,
             &pGame->board
         ) )
    {
        return false;
    }

    //* Player must own square
    if ( !doesPlayerOwnStack(
             pEvent,
             &pGame->board
         ) )
    {
        return false;
    }

    return true;
}

bool validateEventDrop(
    GameEvent const* const pEvent,
    Game const* const pGame
)
{
    //* Cant drop more than currently lifted
    if ( !isDropCountValid(
             pEvent,
             pGame->stackBuffer.stoneCount
         ) )
    {
        return false;
    }

    //* Top vs. captive must obey rules
    if ( !isCaptiveValid(
             pEvent,
             &pGame->board
         ) )
    {
        return false;
    }

    return true;
}

bool isStoneTypeAvailable(
    GameEvent const* const pEvent,
    Reserves const* const pReserves
)
{
    if ( pEvent->stoneType != STONE_TYPE_CAP )
    {
        if ( pReserves->regular[pEvent->playerId] > 0 )
        {
            return true;
        }
    }
    else
    {
        if ( pReserves->capstone[pEvent->playerId] > 0 )
        {
            return true;
        }
    }

    return false;
}

bool isFileXOnBoard(
    GameEvent const* const pEvent,
    int const boardWidth
)
{
    int const pos = pEvent->fileX;

    return ( pos < boardWidth
             && pos >= 0 )
               ? true
               : false;
}

bool isRankYOnBoard(
    GameEvent const* const pEvent,
    int const boardWidth
)
{
    int const pos = pEvent->rankY;

    return ( pos < boardWidth
             && pos >= 0 )
               ? true
               : false;
}

bool isSquareEmpty(
    GameEvent const* const pEvent,
    Board const* const pBoard
)
{
    return ( pBoard->stoneCounts[positionToSquare(
                 pEvent->fileX,
                 pEvent->rankY,
                 pBoard->width
             )]
             > 0 )
               ? false
               : true;
}

bool doesPlayerOwnStack(
    GameEvent const* const pEvent,
    Board const* const pBoard
)
{
    int const squareIdx = positionToSquare(
        pEvent->fileX,
        pEvent->rankY,
        pBoard->width
    );

    return ( pBoard->stoneIds[squareToStackIndex( squareIdx, pBoard->stackCapacity ) + pBoard->stoneCounts[squareIdx] - 1]
             == pEvent->playerId )
               ? true
               : false;
}

bool isDropCountValid(
    GameEvent const* const pEvent,
    int const stackBufferStoneCount
)
{
    return ( pEvent->dropCount
             > stackBufferStoneCount )
               ? false
               : true;
}

bool isCaptiveValid(
    GameEvent const* const pEvent,
    Board const* const pBoard
)
{
    int const squareIdx = positionToSquare(
        pEvent->fileX,
        pEvent->rankY,
        pBoard->width
    );

    StoneType const captiveType = pBoard->types[squareIdx];
    StoneType const droppedType = pEvent->stoneType;

    /// Nothing can be placed on capstone
    if ( captiveType == STONE_TYPE_CAP )
    {
        return false;
    }

    /// Only capstone can flatten standing
    if ( captiveType == STONE_TYPE_STANDING
         && droppedType != STONE_TYPE_CAP )
    {
        return false;
    }

    return true;
}

