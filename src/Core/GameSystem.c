#include "GameSystem.h"

#include "ActionTypeId.h"
#include "BoardSystem.h"
#include "FileId.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "PositionSystem.h"
#include "RankId.h"
#include "ReservesSystem.h"
#include "StackBufferSystem.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

Game newGame( int boardWidth )
{
    if ( !boardWidth )
    {
        boardWidth = BOARD_WIDTH_DEFAULT;
    }

    return (Game){
        .board = newBoard( boardWidth ),
        .stackBuffer = newStackBuffer(),
        .reserves = newReserves( boardWidth ),
    };
}

//* Core functions
void applyEvent(
    Game* const pGame,
    GameEvent const* const pEvent
)
{
    switch ( pEvent->actionType )
    {
        default:
        {
            assert( !"No actiontype set" );

            return;
        }

        case ACTION_TYPE_PLACE:
        {
            placeStone(
                pGame,
                pEvent->playerId,
                pEvent->fileX,
                pEvent->rankY,
                pEvent->stoneType
            );

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            liftStack(
                pGame,
                pEvent->fileX,
                pEvent->rankY
            );

            return;
        }

        case ACTION_TYPE_DROP:
        {
            for ( int i = 0; i < pEvent->dropCount; ++i )
            {
                dropStone(
                    pGame,
                    pEvent->fileX,
                    pEvent->rankY
                );
            }

            return;
        }
    }
}

void placeStone(
    Game* const pGame,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY,
    StoneType const stoneType
)
{
    int const squareIdx
        = positionToSquare(
            fileX,
            rankY,
            pGame->board.width
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

void liftStack(
    Game* const pGame,
    FileId const fileX,
    RankId const rankY
)
{
    int const squareIdx
        = positionToSquare(
            fileX,
            rankY,
            pGame->board.width
        );

    assert(
        pGame->board.stoneCounts[squareIdx] > 0
        && "Cannot pick up empty stack"
    );

    //* INFO: [Rule] StackBuffer stone count must cap at boardWidth
    int const stoneCount
        = ( pGame->board.stoneCounts[squareIdx]
            > pGame->board.width )
              ? pGame->board.width
              : pGame->board.stoneCounts[squareIdx];

    int const stoneType = pGame->board.types[squareIdx];

    resetBuffer(
        &pGame->stackBuffer,
        stoneType
    );

    //* Add stones to buffer
    int const topStoneIdx
        = squareToStackIndex(
              squareIdx,
              pGame->board.stackCapacity
          )
          + ( pGame->board.stoneCounts[squareIdx] - 1 );

    for ( int i = 0; i < stoneCount; ++i )
    {
        appendToBuffer(
            &pGame->stackBuffer,
            pGame->board.stoneIds[topStoneIdx - i]
        );
    }

    //* Remove stones from stack
    takeFromStack(
        &pGame->board,
        squareIdx,
        stoneCount
    );
}

void dropStone(
    Game* const pGame,
    FileId const fileX,
    RankId const rankY
)
{
    int const squareIdx
        = positionToSquare(
            fileX,
            rankY,
            pGame->board.width
        );

    StoneType const captiveStoneType = pGame->board.types[squareIdx];

    //* INFO: [Rule] No stone can be put onto capstone
    assert(
        captiveStoneType != STONE_TYPE_CAP
        && "No stone can be placed onto capstone"
    );

    StoneType const droppedStoneType
        = ( pGame->stackBuffer.stoneCount > 1 )
              ? STONE_TYPE_FLAT
              : pGame->stackBuffer.stoneType;

    //* INFO: [Rule] Only capstone can flatten standing stones
    assert(
        !( captiveStoneType == STONE_TYPE_STANDING
           && droppedStoneType != STONE_TYPE_CAP )
        && "Only capstone can be placed on wall (=flatten)"
    );

    PlayerId const playerId = pGame->stackBuffer.stoneIds[pGame->stackBuffer.stoneCount - 1];

    putOntoStack(
        &pGame->board,
        playerId,
        squareIdx,
        droppedStoneType
    );

    dropFromBuffer( &pGame->stackBuffer );
}

