#include "BoardSystem.h"

#include "Board.h"
#include "GameConstantsSystem.h"
#include "PlayerId.h"
#include "PositionSystem.h"
#include "StoneType.h"
#include <assert.h>

Board newBoard( int const boardWidth )
{
    Board board = {
        .stoneIds = { 0 },
        .counts = { 0 },
        .types = { 0 },
        .stackCapacity = 2 * getBaseRegularStoneReserves( boardWidth )
                         + (int)( 0 != getBaseCapstoneReserves( boardWidth ) ),
        .width = boardWidth
    };

    int const arraySize = boardWidth * boardWidth * board.stackCapacity;

    for ( int idx = 0; idx < arraySize; ++idx )
    {
        board.stoneIds[idx] = PLAYER_NONE;
    }

    return board;
}

void putOntoStack(
    Board* const pBoard,
    int const squareIdx,
    PlayerId const playerId,
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
    pBoard->stoneIds[stackIdx + pBoard->counts[squareIdx]] = playerId;

    //* Increase stack count
    ++pBoard->counts[squareIdx];
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
        stoneCount <= pBoard->counts[squareIdx]
        && "Invalid stoneCount"
    );

    //* Decrease stack count
    pBoard->counts[squareIdx] -= stoneCount;

    //* Set stone type
    pBoard->types[squareIdx] = STONE_TYPE_FLAT;
}
