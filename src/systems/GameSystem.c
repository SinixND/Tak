#include "GameSystem.h"

#include "ActionType.h"
#include "BoardSystem.h"
#include "FileId.h"
#include "GameConstants.h"
#include "HistorySystem.h"
#include "PlayerAction.h"
#include "PlayerId.h"
#include "PlayersSystem.h"
#include "PositionSystem.h"
#include "RankId.h"
#include "StackBufferSystem.h"
#include "StoneType.h"
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
    int const squareIdx
        = positionToSquare(
            fileX,
            rankY,
            pGame->board.width
        );

    //* INFO: [Rule] Can only place on empty squares
    assert(
        pGame->board.counts[squareIdx] == 0
        && "Can only place on empty square"
    );

    takeFromReserves(
        &pGame->players,
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
        &pGame->players,
        lastAction.playerId,
        lastAction.stoneType
    );

    //* Adjust history
    undoHistory( &pGame->history );
}

void redoPlaceStone( Game* const pGame )
{
    assert(
        pGame->history.redoCount > 0 && "Nothing to redo"
    );

    PlayerAction const nextAction = pGame->history.actions[pGame->history.lastActionIdx + 1];

    //* INFO: [Rule] Can only place on empty squares
    assert(
        pGame->board.counts[nextAction.squareIdx] == 0
        && "Can only place on empty square"
    );

    takeFromReserves(
        &pGame->players,
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

void pickUpStack(
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
        pGame->board.counts[squareIdx] > 0
        && "Cannot pick up empty stack"
    );

    int const topStoneIdx
        = squareToStackIndex(
              squareIdx,
              pGame->board.stackCapacity
          )
          + ( pGame->board.counts[squareIdx] - 1 );

    //* INFO: [Rule] StackBuffer stone count must cap at boardWidth
    int const stoneCount
        = ( pGame->board.counts[squareIdx]
            > pGame->board.width )
              ? pGame->board.width
              : pGame->board.counts[squareIdx];

    int const stoneType = pGame->board.types[squareIdx];

    resetBuffer(
        &pGame->stackBuffer,
        stoneType
    );

    //* Add stones to buffer
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
    recordPickupAction(
        &pGame->history,
        squareIdx,
        topStoneIdx,
        stoneType,
        stoneCount
    );
}

void undoPickupStack( Game* const pGame )
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

void redoPickupStack( Game* const pGame )
{
    assert(
        pGame->history.redoCount > 0 && "Nothing to redo"
    );

    PlayerAction const nextAction = pGame->history.actions[pGame->history.lastActionIdx + 1];

    assert(
        pGame->board.counts[nextAction.squareIdx] > 0
        && "Cannot pick up empty stack"
    );

    resetBuffer(
        &pGame->stackBuffer,
        nextAction.stoneType
    );

    //* Add stones to buffer
    for ( int i = 0; i < nextAction.stoneCount; ++i )
    {
        appendToBuffer(
            &pGame->stackBuffer,
            pGame->board.stoneIds[nextAction.topStoneIdx - i]
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

    //* INFO: [Rule] Capstone can flatten standing stones
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

void undoDropStone( Game* const pGame )
{
    PlayerAction const lastAction = pGame->history.actions[pGame->history.lastActionIdx];

    //* INFO: [Rule] No stone can be put onto capstone
    assert(
        pGame->board.counts[lastAction.squareIdx] > 0
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

void undo( Game* const pGame )
{
    assert(
        pGame->history.lastActionIdx > 0
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

        case ACTION_TYPE_PICKUP:
        {
            undoPickupStack( pGame );
            break;
        }
    }
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

        case ACTION_TYPE_PICKUP:
        {
            redoPickupStack( pGame );

            break;
        }
    }
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

    undo( pGame );
    redo( pGame );

    putOntoStack(
        &pGame->board,
        PLAYER_BLACK,
        0,
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

