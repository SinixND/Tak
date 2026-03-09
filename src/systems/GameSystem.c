#include "GameSystem.h"

#include "BoardSystem.h"
#include "FileId.h"
#include "GameConstants.h"
#include "HistorySystem.h"
#include "PlayerId.h"
#include "PlayersSystem.h"
#include "PositionSystem.h"
#include "RankId.h"
#include "StackBufferSystem.h"
#include "StoneType.h"
#include <assert.h>

Game newGame( int boardWidth )
{
    if ( !boardWidth )
    {
        boardWidth = BOARD_WIDTH_DEFAULT;
    }

    return (Game){
        .board = newBoard( boardWidth ),
        .stackBuffer = newStackBuffer(),
        .players = newPlayers( boardWidth ),
    };
}

void placeStone(
    Game* const pGame,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY,
    StoneType const stoneType
)
{
    int const squareIdx = positionToSquare(
        fileX,
        rankY,
        pGame->board.width
    );

    //* INFO: [Rule] Can only place on empty squares
    assert(
        pGame->board.counts[squareIdx] == 0
        && "Can only place on empty square"
    );

    assert(
        pGame->board.types[squareIdx] == STONE_TYPE_NONE
        && "Can only place on empty square"
    );

    takeFromReserves(
        &pGame->players,
        playerId,
        stoneType
    );

    putOntoStack(
        &pGame->board,
        squareIdx,
        playerId,
        stoneType
    );

    //* Add action to undo stack
    recordPlacementAction(
        &pGame->history,
        stoneType,
        fileX,
        rankY
    );
}

void pickUpStack(
    Game* const pGame,
    FileId const fileX,
    RankId const rankY
)
{
    int const squareIdx = positionToSquare(
        fileX,
        rankY,
        pGame->board.width
    );

    int stoneCount = pGame->board.counts[squareIdx];
    int const boardWidth = pGame->board.width;

    //* INFO: [Rule] StackBuffer stone count must cap at boardWidth
    stoneCount -= ( stoneCount - boardWidth )
                  & -( stoneCount > boardWidth );

    assert(
        pGame->board.counts[squareIdx] > 0
        && "Cannot pick up empty stack"
    );

    //* Pick up first stone
    int topStoneIdx = squareToStackIndex(
                          squareIdx,
                          pGame->board.stackCapacity
                      )
                      + pGame->board.counts[squareIdx]
                      - 1;

    resetStackBuffer(
        &pGame->stackBuffer,
        pGame->board.stoneIds[topStoneIdx],
        pGame->board.types[squareIdx]
    );

    takeFromStack(
        &pGame->board,
        squareIdx
    );

    //* Adjust local variables: First stone was removed
    --topStoneIdx;
    --stoneCount;

    //* Pick up remaining stones
    for ( int i = 0; i < stoneCount; ++i )
    {
        appendToBuffer(
            &pGame->stackBuffer,
            pGame->board.stoneIds[topStoneIdx]
        );

        takeFromStack(
            &pGame->board,
            squareIdx
        );

        --topStoneIdx;
    }
}

void dropStone(
    Game* const pGame,
    FileId const fileX,
    RankId const rankY
)
{
    int const squareIdx = positionToSquare(
        fileX,
        rankY,
        pGame->board.width
    );

    //* Type if last, else flat
    StoneType const droppedStoneType = STONE_TYPE_FLAT + ( ( pGame->stackBuffer.type - STONE_TYPE_FLAT ) & -( pGame->stackBuffer.count <= 1 ) );
    StoneType const stackType = pGame->board.types[squareIdx];

    //* INFO: [Rule] Capstone can flatten stating stones
    assert(
        stackType != STONE_TYPE_CAP
        && "No stone can be placed onto capstone"
    );

    assert(
        !( droppedStoneType != STONE_TYPE_CAP
           && stackType == STONE_TYPE_STANDING )
        && "Only capstone can be placed on wall (=flatten)"
    );

    putOntoStack(
        &pGame->board,
        squareIdx,
        pGame->stackBuffer.stoneIds[pGame->stackBuffer.count - 1],
        droppedStoneType
    );

    dropFromBuffer( &pGame->stackBuffer );
}

void demo( Game* const pGame )
{
    placeStone(
        pGame,
        PLAYER_WHITE,
        0,
        0,
        STONE_TYPE_FLAT
    );

    putOntoStack(
        &pGame->board,
        0,
        PLAYER_BLACK,
        STONE_TYPE_STANDING
    );

    pickUpStack(
        pGame,
        0,
        0
    );

    dropStone(
        pGame,
        0,
        1
    );
}

