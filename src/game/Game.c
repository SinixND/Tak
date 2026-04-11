#include "Game.h"

#include "Board.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "PositionSystem.h"
#include "Reserves.h"
#include "StackBuffer.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

Game newGame( int boardSize )
{
    if ( !boardSize )
    {
        boardSize = BOARD_SIZE_DEFAULT;
    }

    return (Game){
        .board = newBoard( boardSize ),
        .stackBuffer = newStackBuffer(),
        .reserves = newReserves( boardSize ),
    };
}

void placeStone(
    Game* const pGame,
    PlayerId const playerId,
    int const squareIdx,
    StoneType const stoneType
)
{
    //* INFO: [Rule] Can only place on empty squares
    assert(
        pGame->board.stoneCounts[squareIdx] == 0
        && "Can only place on empty square"
    );

    takeFromReserves(
        &pGame->reserves,
        playerId,
        stoneType
    );

    putOntoStack(
        &pGame->board,
        playerId,
        squareIdx,
        stoneType
    );
}

void takeStone(
    Game* const pGame,
    int const squareIdx
)
{
    Board* const pBoard = &pGame->board;

    assert(
        pBoard->stoneCounts[squareIdx] == 1
        && "Can only take single stone"
    );

    //* Add to reserves
    returnToReserves(
        &pGame->reserves,
        pBoard->stoneIds[squareToStackIndex( squareIdx, pBoard->stackCapacity )],
        pBoard->stackTypes[squareIdx]
    );

    //* Remove from stack
    takeFromStack(
        pBoard,
        squareIdx,
        1
    );
}

void liftStack(
    Game* const pGame,
    int const squareIdx
)
{
    Board* const pBoard = &pGame->board;

    assert(
        pBoard->stoneCounts[squareIdx] > 0
        && "Cannot pick up empty stack"
    );

    //* INFO: [Rule] StackBuffer stone count must cap at boardSize
    int const stoneCount
        = ( pBoard->stoneCounts[squareIdx]
            > pBoard->width )
              ? pBoard->width
              : pBoard->stoneCounts[squareIdx];

    int const stoneType = pBoard->stackTypes[squareIdx];

    resetBuffer(
        &pGame->stackBuffer,
        stoneType
    );

    //* Add stones to buffer
    int const topStoneIdx
        = squareToStackIndex(
              squareIdx,
              pBoard->stackCapacity
          )
          + ( pBoard->stoneCounts[squareIdx] - 1 );

    for ( int i = 0; i < stoneCount; ++i )
    {
        appendToBuffer(
            &pGame->stackBuffer,
            pBoard->stoneIds[topStoneIdx - i]
        );
    }

    //* Remove stones from stack
    takeFromStack(
        pBoard,
        squareIdx,
        stoneCount
    );
}

void dropStack(
    Game* const pGame,
    int const squareIdx
)
{
    StackBuffer* const stackBuffer = &pGame->stackBuffer;

    //* Add stones to stack
    for ( int i = 0; i < ( stackBuffer->stoneCount - 1 ); ++i )
    {
        putOntoStack(
            &pGame->board,
            stackBuffer->stoneIds[( stackBuffer->stoneCount - 1 ) - i],
            squareIdx,
            STONE_TYPE_FLAT
        );
    }

    //* Add last stone to stack
    putOntoStack(
        &pGame->board,
        stackBuffer->stoneIds[( stackBuffer->stoneCount - 1 )],
        squareIdx,
        stackBuffer->stoneType
    );

    //* Empty buffer
    stackBuffer->stoneCount = 0;
}

void dropStone(
    Game* const pGame,
    int const squareIdx
)
{
    StackBuffer* const stackBuffer = &pGame->stackBuffer;
    StoneType const captiveStoneType = pGame->board.stackTypes[squareIdx];

    //* INFO: [Rule] No stone can be put onto capstone
    assert(
        captiveStoneType != STONE_TYPE_CAP
        && "No stone can be placed onto capstone"
    );

    StoneType const droppedStoneType
        = ( stackBuffer->stoneCount > 1 )
              ? STONE_TYPE_FLAT
              : stackBuffer->stoneType;

    //* INFO: [Rule] Only capstone can flatten standing stones
    assert(
        !( captiveStoneType == STONE_TYPE_STANDING
           && droppedStoneType != STONE_TYPE_CAP )
        && "Only capstone can be placed on wall (=flatten)"
    );

    PlayerId const playerId = stackBuffer->stoneIds[stackBuffer->stoneCount - 1];

    putOntoStack(
        &pGame->board,
        playerId,
        squareIdx,
        droppedStoneType
    );

    dropFromBuffer( &pGame->stackBuffer );
}

void liftStone(
    Game* const pGame,
    int const squareIdx,
    bool const flattened
)
{
    Board* const pBoard = &pGame->board;

    assert(
        pBoard->stoneCounts[squareIdx] > 0
        && "Cant undo drop from emtpy square"
    );

    PlayerId const playerId
        = pBoard->stoneIds[squareToStackIndex( squareIdx, pBoard->stackCapacity ) + ( pBoard->stoneCounts[squareIdx] - 1 )];

    appendToBuffer(
        &pGame->stackBuffer,
        playerId
    );

    takeFromStack(
        pBoard,
        squareIdx,
        1
    );

    //* Make stackType 'standing' if drop flattened
    pBoard->stackTypes[squareIdx]
        = flattened
              ? STONE_TYPE_STANDING
              : STONE_TYPE_FLAT;
}
