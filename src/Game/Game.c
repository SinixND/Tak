#include "Game.h"

#include "Board.h"
#include "PlayerId.h"
#include "Position.h"
#include "Reserves.h"
#include "StackBuffer.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

Game newGame( int boardSize )
{
    assert(
        ( boardSize > 2 )
        && "BoardSize too small"
    );

    assert(
        ( boardSize < 9 )
        && "BoardSize too big"
    );

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
    assert(
        pGame
        && "Pointer is nullptr"
    );

    assert(
        playerId != PLAYER_NONE
        && "Invalid player Id"
    );

    assert(
        squareIdx >= 0
        && squareIdx < ( pGame->board.size * pGame->board.size )
        && "Invalid square index"
    );

    assert(
        stoneType != STONE_TYPE_NONE
        && "Invalid stone type"
    );

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
    assert(
        pGame
        && "Pointer is nullptr"
    );

    assert(
        squareIdx >= 0
        && squareIdx < ( pGame->board.size * pGame->board.size )
        && "Invalid square index"
    );

    Board* const pBoard = &pGame->board;

    assert(
        pBoard->stoneCounts[squareIdx] == 1
        && "Can only take single stone"
    );

    //* Add to reserves
    returnToReserves(
        &pGame->reserves,
        pBoard->stoneIds[squareToStackIndex(
            squareIdx,
            pBoard->size
        )],
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
    assert(
        pGame
        && "Pointer is nullptr"
    );

    assert(
        squareIdx >= 0
        && squareIdx < ( pGame->board.size * pGame->board.size )
        && "Invalid square index"
    );

    Board* const pBoard = &pGame->board;

    assert(
        pBoard->stoneCounts[squareIdx] > 0
        && "Cannot pick up empty stack"
    );

    //* INFO: [Rule] StackBuffer stone count must cap at boardSize
    int const stoneCount
        = ( pBoard->stoneCounts[squareIdx]
            > pBoard->size )
              ? pBoard->size
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
              pBoard->size
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
    assert(
        pGame
        && "Pointer is nullptr"
    );

    assert(
        squareIdx >= 0
        && squareIdx < ( pGame->board.size * pGame->board.size )
        && "Invalid square index"
    );

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
    assert(
        pGame
        && "Pointer is nullptr"
    );

    assert(
        squareIdx >= 0
        && squareIdx < ( pGame->board.size * pGame->board.size )
        && "Invalid square index"
    );

    StackBuffer* const pStackBuffer = &pGame->stackBuffer;
    StoneType const captiveStoneType = pGame->board.stackTypes[squareIdx];

    //* INFO: [Rule] No stone can be put onto capstone
    assert(
        captiveStoneType != STONE_TYPE_CAP
        && "No stone can be placed onto capstone"
    );

    StoneType const droppedStoneType
        = ( pStackBuffer->stoneCount > 1 )
              ? STONE_TYPE_FLAT
              : pStackBuffer->stoneType;

    //* INFO: [Rule] Only capstone can flatten standing stones
    assert(
        !( captiveStoneType == STONE_TYPE_STANDING
           && droppedStoneType != STONE_TYPE_CAP )
        && "Only capstone can be placed on wall (=flatten)"
    );

    PlayerId const playerId = pStackBuffer->stoneIds[pStackBuffer->stoneCount - 1];

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
    assert(
        pGame
        && "Pointer is nullptr"
    );

    assert(
        squareIdx >= 0
        && squareIdx < ( pGame->board.size * pGame->board.size )
        && "Invalid square index"
    );

    Board* const pBoard = &pGame->board;

    assert(
        pBoard->stoneCounts[squareIdx] > 0
        && "Cant undo drop from emtpy square"
    );

    PlayerId const playerId
        = pBoard->stoneIds[squareToStackIndex( squareIdx, pBoard->size ) + ( pBoard->stoneCounts[squareIdx] - 1 )];

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

void executeEvent(
    Game* const pGame,
    Event const* const pEvent
)
{
    assert(
        pGame
        && "Pointer is nullptr"
    );

    assert(
        pEvent
        && "Pointer is nullptr"
    );

    switch ( pEvent->actionType )
    {
        default:
        {
            assert( !"No action type set" );

            return;
        }

        case ACTION_TYPE_PLACE:
        {
            placeStone(
                pGame,
                pEvent->playerId,
                pEvent->squareIdx,
                pEvent->stoneType
            );

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            liftStack(
                pGame,
                pEvent->squareIdx
            );

            return;
        }

        case ACTION_TYPE_DROP:
        {
            for ( int i = 0; i < pEvent->dropCount; ++i )
            {
                dropStone(
                    pGame,
                    pEvent->squareIdx
                );
            }

            return;
        }
    }
}
