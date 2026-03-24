#include "BoardSystem.h"

#include "Board.h"
#include "GameConstants.h"
#include "GameConstantsSystem.h"
#include "PlayerId.h"
#include "PositionSystem.h"
#include "StoneType.h"
#include <assert.h>

Board newBoard( int const boardWidth )
{
    Board board = {
        .stackCapacity = 2 * getBaseRegularStoneReserves( boardWidth )
                         + (int)( 0 != getBaseCapstoneReserves( boardWidth ) ), // can only have one per stack
        .width = boardWidth
    };

    int const squareCount = boardWidth * boardWidth;
    int const arraySize = squareCount * board.stackCapacity;

    for ( int idx = 0; idx < squareCount; ++idx )
    {
        board.types[idx] = STONE_TYPE_NONE;
        board.stoneCounts[idx] = 0;
    }

    for ( int idx = 0; idx < arraySize; ++idx )
    {
        board.stoneIds[idx] = PLAYER_NONE;
    }

    return board;
}

void putOntoStack(
    Board* const pBoard,
    PlayerId const playerId,
    int const squareIdx,
    StoneType const stoneType
)
{
    assert(
        ( squareIdx >= 0 )
        && "Invalid squareIdx"
    );

    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    assert(
        stoneType != STONE_TYPE_NONE
        && "Invalid stoneType"
    );

    //* Set stack type
    pBoard->types[squareIdx] = stoneType;

    int const stackIdx
        = squareToStackIndex(
            squareIdx,
            pBoard->stackCapacity
        );

    //* Add playerId
    pBoard->stoneIds[stackIdx + pBoard->stoneCounts[squareIdx]] = playerId;

    //* Increase stack count
    ++pBoard->stoneCounts[squareIdx];
}

void takeFromStack(
    Board* const pBoard,
    int const squareIdx,
    int const stoneCount
)
{
    assert(
        squareIdx >= 0
        && "Invalid squareIdx"
    );

    assert(
        stoneCount <= pBoard->stoneCounts[squareIdx]
        && "Invalid stoneCount"
    );

    //* Decrease stack count
    pBoard->stoneCounts[squareIdx] -= stoneCount;

    //* Set stack type
    pBoard->types[squareIdx] = STONE_TYPE_FLAT;
}
