#include "Board.h"

#include "GameConstants.h"
#include "PlayerId.h"
#include "PositionSystem.h"
#include "StoneTypeId.h"
#include <assert.h>

Board newBoard( int const boardSize )
{
    Board board = {
        .stackCapacity = getStackCapacity( boardSize ), // can only have one per stack
        .width = boardSize
    };

    int const squareCount = boardSize * boardSize;
    int const arraySize = squareCount * board.stackCapacity;

    for ( int idx = 0; idx < squareCount; ++idx )
    {
        board.stackTypes[idx] = STONE_TYPE_NONE;
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
    pBoard->stackTypes[squareIdx] = stoneType;

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
    pBoard->stackTypes[squareIdx] = STONE_TYPE_FLAT;
}
