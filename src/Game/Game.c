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
        ( boardSize >= BOARD_SIZE_MIN )
        && ( boardSize <= BOARD_SIZE_MAX )
        && "Board size invalid"
    );

    return (Game){
        .board = newBoard( boardSize ),
        .stackBuffer = newStackBuffer(),
        .reserves = newReserves( boardSize ),
        .scores = { 0, 0 },
        .activePlayer = PLAYER_WHITE,
    };
}

void changeActivePlayer( Game* const pGame )
{
    assert(
        pGame
        && "Pointer is nullptr"
    );

    assert(
        pGame->activePlayer != PLAYER_NONE
        && "PlayerId invalid"
    );

    if ( pGame->activePlayer == PLAYER_WHITE )
    {
        pGame->activePlayer = PLAYER_BLACK;
    }
    else
    {
        pGame->activePlayer = PLAYER_WHITE;
    }
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
        && "Player Id invalid"
    );

    assert(
        squareIdx >= 0
        && squareIdx < pGame->board.squareCount
        && "Square index invalid"
    );

    assert(
        stoneType != STONE_TYPE_NONE
        && "Stone type invalid"
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
        && squareIdx < pGame->board.squareCount
        && "Square index invalid"
    );

    Board* const pBoard = &pGame->board;

    assert(
        pBoard->stoneCounts[squareIdx] == 1
        && "Can only take single stone"
    );

    /// Add to reserves
    returnToReserves(
        &pGame->reserves,
        pBoard->stackIds[squareIdx],
        pBoard->stackTypes[squareIdx]
    );

    /// Remove from stack
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
        && squareIdx < pGame->board.squareCount
        && "Square index invalid"
    );

    Board* const pBoard = &pGame->board;

    assert(
        pBoard->stoneCounts[squareIdx] > 0
        && "Cannot pick up empty stack"
    );

    /// Cap count at board size
    int const count = pBoard->stoneCounts[squareIdx];
    int const size = pBoard->size;

    int const stoneCount
        = count
          - ( ( count > size )
              * ( count - size ) );

    int const stoneType = pBoard->stackTypes[squareIdx];

    resetBuffer(
        &pGame->stackBuffer,
        stoneType
    );

    /// Add stones to buffer
    int const topStoneIdx
        = squareToStackIndex(
              squareIdx,
              pBoard->size
          )
          + ( pBoard->stoneCounts[squareIdx] - 1 );

    for ( int offset = 0; offset < stoneCount; ++offset )
    {
        appendToBuffer(
            &pGame->stackBuffer,
            pBoard->stoneIds[topStoneIdx - offset]
        );
    }

    /// Remove stones from stack
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
        && squareIdx < pGame->board.squareCount
        && "Square index invalid"
    );

    StackBuffer* const stackBuffer = &pGame->stackBuffer;

    /// Add stones to stack
    /// Offset start from 1 due to count vs. index
    for ( int offset = 1; offset < stackBuffer->stoneCount; ++offset )
    {
        putOntoStack(
            &pGame->board,
            stackBuffer->stoneIds[stackBuffer->stoneCount - offset],
            squareIdx,
            STONE_TYPE_FLAT
        );
    }

    /// Add last stone to stack
    putOntoStack(
        &pGame->board,
        stackBuffer->stoneIds[0],
        squareIdx,
        stackBuffer->stackType
    );

    /// Empty buffer
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
        && squareIdx < pGame->board.squareCount
        && "Square index invalid"
    );

    StackBuffer* const pStackBuffer = &pGame->stackBuffer;

    StoneType const droppedStoneType
        = ( pStackBuffer->stoneCount > 1 )
              ? STONE_TYPE_FLAT
              : pStackBuffer->stackType;

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
        && squareIdx < pGame->board.squareCount
        && "Square index invalid"
    );

    Board* const pBoard = &pGame->board;

    assert(
        pBoard->stoneCounts[squareIdx] > 0
        && "Cant lift from emtpy square"
    );

    PlayerId const playerId
        = pBoard->stoneIds[squareToStackIndex( squareIdx, pBoard->size ) + ( pBoard->stoneCounts[squareIdx] - 1 )];

    if ( pGame->stackBuffer.stoneCount < 1 )
    {
        pGame->stackBuffer.stackType = pBoard->stackTypes[squareIdx];
    }

    appendToBuffer(
        &pGame->stackBuffer,
        playerId
    );

    takeFromStack(
        pBoard,
        squareIdx,
        1
    );

    /// Make stackType 'standing' if previous drop flattened
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

        default:
        {
            assert( !"No action type set" );
            return;
        }
    }
}

void updateScore( Game* const pGame )
{
    assert(
        pGame
        && "Pointer is nullptr"
    );

    /// Reset scores
    pGame->scores[0] = 0;
    pGame->scores[1] = 0;

    /// Count flats
    int const squareCount = pGame->board.squareCount;

    for ( int squareIdx = 0; squareIdx < squareCount; ++squareIdx )
    {
        if ( pGame->board.stackTypes[squareIdx] == STONE_TYPE_FLAT )
        {
            ++pGame->scores[pGame->board.stackIds[squareIdx]];
        }
    }
}
