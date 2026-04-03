#include "GameSystem.h"

#include "ActionTypeId.h"
#include "BoardSystem.h"
#include "FileId.h"
#include "GameConstants.h"
#include "HistorySystem.h"
#include "PlayerAction.h"
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
        .history = newHistory(),
        .stackBuffer = newStackBuffer(),
        .reserves = newReserves( boardWidth ),
    };
}

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

//* Core functions
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

    //* Add action to undo stack
    recordPlacementAction(
        &pGame->history,
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

    //* Add action to undo stack
    recordLiftAction(
        &pGame->history,
        squareIdx,
        stoneType,
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

    //* Add action to undo stack
    recordDropAction(
        &pGame->history,
        playerId,
        squareIdx,
        droppedStoneType,
        (bool)( ( droppedStoneType == STONE_TYPE_CAP ) && ( captiveStoneType == STONE_TYPE_STANDING ) )
    );
}

//* Undo functions
void undoPlaceStone( Game* const pGame )
{
    PlayerAction const lastAction = pGame->history.actions[pGame->history.lastActionIdx];

    //* Undo putOnStack
    takeFromStack(
        &pGame->board,
        lastAction.squareIdx,
        1
    );

    //* Undo takeFromReserves
    returnToReserves(
        &pGame->reserves,
        lastAction.playerId,
        lastAction.stoneType
    );

    //* Adjust history
    undoHistory( &pGame->history );
}

void undoLiftStack( Game* const pGame )
{
    PlayerAction const lastAction = pGame->history.actions[pGame->history.lastActionIdx];

    //* Add stones to stack
    for ( int i = 0; i < lastAction.stoneCount; ++i )
    {
        putOntoStack(
            &pGame->board,
            pGame->stackBuffer.stoneIds[( lastAction.stoneCount - 1 ) - i],
            lastAction.squareIdx,
            lastAction.stoneType
        );
    }

    //* Empty buffer
    pGame->stackBuffer.stoneCount = 0;

    //* Adjust history
    undoHistory( &pGame->history );
}

void undoDropStone( Game* const pGame )
{
    PlayerAction const lastAction = pGame->history.actions[pGame->history.lastActionIdx];

    //* INFO: [Rule] No stone can be put onto capstone
    assert(
        pGame->board.stoneCounts[lastAction.squareIdx] > 0
        && "Cant undo drop from emtpy square"
    );

    appendToBuffer(
        &pGame->stackBuffer,
        lastAction.playerId
    );

    takeFromStack(
        &pGame->board,
        lastAction.squareIdx,
        lastAction.stoneCount
    );

    //* Make stackType 'standing' if drop flattened
    pGame->board.types[lastAction.squareIdx]
        = lastAction.flattened
              ? STONE_TYPE_STANDING
              : STONE_TYPE_FLAT;

    //* Adjust history
    undoHistory( &pGame->history );
}

void undo( Game* const pGame )
{
    assert(
        pGame->history.lastActionIdx >= 0
        && "Nothing to undo"
    );

    switch ( pGame->history.actions[pGame->history.lastActionIdx].actionType )
    {
        default:
        {
            assert( !"Missing undo case" );
            break;
        }

        case ACTION_TYPE_PLACE:
        {
            undoPlaceStone( pGame );
            break;
        }

        case ACTION_TYPE_LIFT:
        {
            undoLiftStack( pGame );
            break;
        }

        case ACTION_TYPE_DROP:
        {
            undoDropStone( pGame );
            break;
        }
    }
}

//* Redo functions
void redoPlaceStone( Game* const pGame )
{
    assert(
        pGame->history.redoCount > 0 && "Nothing to redo"
    );

    PlayerAction const nextAction = pGame->history.actions[pGame->history.lastActionIdx + 1];

    //* INFO: [Rule] Can only place on empty squares
    assert(
        pGame->board.stoneCounts[nextAction.squareIdx] == 0
        && "Can only place on empty square"
    );

    takeFromReserves(
        &pGame->reserves,
        nextAction.playerId,
        nextAction.stoneType
    );

    putOntoStack(
        &pGame->board,
        nextAction.playerId,
        nextAction.squareIdx,
        nextAction.stoneType
    );

    //* Adjust history
    redoHistory( &pGame->history );
}

void redoLiftStack( Game* const pGame )
{
    assert(
        pGame->history.redoCount > 0 && "Nothing to redo"
    );

    PlayerAction const nextAction = pGame->history.actions[pGame->history.lastActionIdx + 1];

    assert(
        pGame->board.stoneCounts[nextAction.squareIdx] > 0
        && "Cannot pick up empty stack"
    );

    resetBuffer(
        &pGame->stackBuffer,
        nextAction.stoneType
    );

    //* Add stones to buffer
    int const topStoneIdx
        = squareToStackIndex(
              nextAction.squareIdx,
              pGame->board.stackCapacity
          )
          + ( pGame->board.stoneCounts[nextAction.squareIdx] - 1 );

    for ( int i = 0; i < nextAction.stoneCount; ++i )
    {
        appendToBuffer(
            &pGame->stackBuffer,
            pGame->board.stoneIds[topStoneIdx - i]
        );
    }

    //* Remove stones from stack
    takeFromStack(
        &pGame->board,
        nextAction.squareIdx,
        nextAction.stoneCount
    );

    //* Adjust history
    redoHistory( &pGame->history );
}

void redoDropStone( Game* const pGame )
{
    assert(
        pGame->history.redoCount > 0 && "Nothing to redo"
    );

    PlayerAction const nextAction = pGame->history.actions[pGame->history.lastActionIdx + 1];

    putOntoStack(
        &pGame->board,
        nextAction.playerId,
        nextAction.squareIdx,
        nextAction.stoneType
    );

    dropFromBuffer( &pGame->stackBuffer );

    //* Adjust history
    redoHistory( &pGame->history );
}

void redo( Game* const pGame )
{
    assert(
        pGame->history.redoCount > 0
        && "Nothing to redo"
    );

    switch ( pGame->history.actions[pGame->history.lastActionIdx + 1].actionType )
    {
        default:
        {
            assert( !"Missing redo case" );
            break;
        }

        case ACTION_TYPE_PLACE:
        {
            redoPlaceStone( pGame );

            break;
        }

        case ACTION_TYPE_LIFT:
        {
            redoLiftStack( pGame );

            break;
        }

        case ACTION_TYPE_DROP:
        {
            redoDropStone( pGame );
            break;
        }
    }
}

