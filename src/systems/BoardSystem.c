#include "BoardSystem.h"

#include "Board.h"
#include "FileId.h"
#include "GameConstantsSystem.h"
#include "PlayerId.h"
#include "PositionSystem.h"
#include "RankId.h"
#include "StoneType.h"
#include <assert.h>
#include <string.h>

Board pushOntoStack(
    Board board,
    int const squareIdx,
    PlayerId const playerId
);

Board newBoard( int const boardWidth )
{
    Board board = {
        .stoneIds = { 0 },
        .counts = { 0 },
        .types = { 0 },
        .stackCapacity = 2 * getBaseRegularStoneReserves( boardWidth ) + 2 * getBaseCapstoneReserves( boardWidth ),
        .width = boardWidth
    };

    memset(
        board.stoneIds,
        PLAYER_NONE,
        sizeof( board.stoneIds ) / sizeof( board.stoneIds[0] )
    );

    return board;
}

Board placeStoneOnBoard(
    Board board,
    FileId const fileX,
    RankId const rankY,
    PlayerId const playerId,
    StoneType const stoneType
)
{
    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    assert(
        stoneType != STONE_TYPE_NONE
        && "Invalid stoneType"
    );

    int const squareIdx = positionToSquare(
        fileX,
        rankY,
        board.width
    );

    //* Set stack type
    board.types[squareIdx] = stoneType;

    board = pushOntoStack(
        board,
        squareIdx,
        playerId
    );

    return board;
}

Board pushOntoStack(
    Board board,
    int const squareIdx,
    PlayerId const playerId
)
{
    assert(
        ( squareIdx >= 0 )
        && "Invalid square value"
    );

    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    int const stackIdx = squareToStackIndex(
        squareIdx,
        board.stackCapacity
    );

    //* Add playerId
    board.stoneIds[stackIdx + board.counts[squareIdx]] = playerId;

    //* Increase stack count
    ++board.counts[squareIdx];

    return board;
}

