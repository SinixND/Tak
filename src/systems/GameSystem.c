#include "GameSystem.h"

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
        fileX,
        rankY,
        stoneType
    );
}

void undoPlaceStone( Game* const pGame )
{
    PlayerAction const lastAction = pGame->history.actions[pGame->history.lastActionIdx];

    //* Undo putOnStack
    takeFromStack(
        &pGame->board,
        positionToSquare(
            lastAction.fileX,
            lastAction.rankY,
            pGame->board.width
        ),
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
    PlayerAction const nextAction = pGame->history.actions[pGame->history.lastActionIdx + 1];

    int const squareIdx
        = positionToSquare(
            nextAction.fileX,
            nextAction.rankY,
            pGame->board.width
        );

    //* INFO: [Rule] Can only place on empty squares
    assert(
        pGame->board.counts[squareIdx] == 0
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
        squareIdx,
        nextAction.stoneType
    );

    //* Adjust history
    redoHistory( &pGame->history );
}

void pickUpStack(
    Game* const pGame,
    PlayerId const playerId,
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

    int topStoneIdx
        = squareToStackIndex(
              squareIdx,
              pGame->board.stackCapacity
          )
          + ( pGame->board.counts[squareIdx] - 1 );

    assert(
        playerId == pGame->board.stoneIds[topStoneIdx]
        && "Only contolling player can pickup stack"
    );

    int stoneCount = pGame->board.counts[squareIdx];
    int const boardWidth = pGame->board.width;

    //* INFO: [Rule] StackBuffer stone count must cap at boardWidth
    stoneCount = ( stoneCount > boardWidth ) ? boardWidth : stoneCount;

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
    recordPickUpAction(
        &pGame->history,
        playerId,
        fileX,
        rankY,
        stoneType,
        stoneCount
    );
}

void undoPickUpStack( Game* const pGame )
{
    PlayerAction const lastAction = pGame->history.actions[pGame->history.lastActionIdx];

    int stoneCount = pGame->stackBuffer.stoneCount;

    assert(
        stoneCount > 0
        && "Cannot undo pickup of empty buffer"
    );

    int const squareIdx
        = positionToSquare(
            lastAction.fileX,
            lastAction.rankY,
            pGame->board.width
        );

    //* Add stones to stack
    for ( int i = 0; i < stoneCount; ++i )
    {
        putOntoStack(
            &pGame->board,
            pGame->stackBuffer.stoneIds[( stoneCount - 1 ) - i],
            squareIdx,
            //* Just use the final type, even if its set for every dropped stone
            pGame->stackBuffer.stoneType
        );
    }

    //* Reset buffer
    resetBuffer(
        &pGame->stackBuffer,
        STONE_TYPE_NONE
    );

    //* Adjust history
    undoHistory( &pGame->history );
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

    StoneType const stackType = pGame->board.types[squareIdx];

    //* INFO: [Rule] No stone can be put onto capstone
    assert(
        stackType != STONE_TYPE_CAP
        && "No stone can be placed onto capstone"
    );

    StoneType const droppedStoneType =
        //
        ( pGame->stackBuffer.stoneCount > 1 )
            ? STONE_TYPE_FLAT
            : pGame->stackBuffer.stoneType;

    //* INFO: [Rule] Capstone can flatten standing stones
    assert(
        !( stackType == STONE_TYPE_STANDING
           && droppedStoneType != STONE_TYPE_CAP )
        && "Only capstone can be placed on wall (=flatten)"
    );

    putOntoStack(
        &pGame->board,
        pGame->stackBuffer.stoneIds[pGame->stackBuffer.stoneCount - 1],
        squareIdx,
        droppedStoneType
    );

    dropFromBuffer( &pGame->stackBuffer );
}

void undo( Game* const pGame )
{
    assert(
        pGame->history.lastActionIdx > 0
        && "Nothing to undo"
    );

    switch ( pGame->history.actions[pGame->history.lastActionIdx].stoneCount )
    {
        default:
        {
            assert( !"Missing undo case" );
            break;
        }

        case 0:
        {
            undoPlaceStone( pGame );
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

    switch ( pGame->history.actions[pGame->history.lastActionIdx + 1].stoneCount )
    {
        default:
        {
            assert( !"Missing redo case" );
            break;
        }

        case 0:
        {
            redoPlaceStone( pGame );

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
        PLAYER_BLACK,
        0,
        0
    );

    dropStone(
        pGame,
        0,
        1
    );
}

