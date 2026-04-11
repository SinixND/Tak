#include "RuleValidation.h"

#include "Event.h"
#include "Game.h"
#include "PositionSystem.h"
#include <stdbool.h>

bool validateEventPlace(
    Event const* const pEvent,
    Game const* const pGame
)
{
    Board const* const pBoard = &pGame->board;

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
             pBoard->width
         ) )
    {
        return false;
    }

    //* RankY on board
    if ( !isRankYOnBoard(
             pEvent,
             pBoard->width
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
    Event const* const pEvent,
    Game const* const pGame
)
{
    Board const* const pBoard = &pGame->board;

    //* FileX on board
    if ( !isFileXOnBoard(
             pEvent,
             pBoard->width
         ) )
    {
        return false;
    }

    //* RankY on board
    if ( !isRankYOnBoard(
             pEvent,
             pBoard->width
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
    Event const* const pEvent,
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
    Event const* const pEvent,
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
    Event const* const pEvent,
    int const boardSize
)
{
    int const pos = pEvent->fileX;

    return ( pos < boardSize
             && pos >= 0 )
               ? true
               : false;
}

bool isRankYOnBoard(
    Event const* const pEvent,
    int const boardSize
)
{
    int const pos = pEvent->rankY;

    return ( pos < boardSize
             && pos >= 0 )
               ? true
               : false;
}

bool isSquareEmpty(
    Event const* const pEvent,
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
    Event const* const pEvent,
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
    Event const* const pEvent,
    int const stackBufferStoneCount
)
{
    return ( pEvent->dropCount
             > stackBufferStoneCount )
               ? false
               : true;
}

bool isCaptiveValid(
    Event const* const pEvent,
    Board const* const pBoard
)
{
    int const squareIdx = positionToSquare(
        pEvent->fileX,
        pEvent->rankY,
        pBoard->width
    );

    StoneType const captiveType = pBoard->stackTypes[squareIdx];
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

