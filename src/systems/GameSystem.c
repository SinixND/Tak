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
    //* Adjust history
    redoHistory( &pGame->history );

    PlayerAction const nextAction = pGame->history.actions[pGame->history.lastActionIdx];

    int const squareIdx = positionToSquare(
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
        squareIdx,
        nextAction.playerId,
        nextAction.stoneType
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

    assert(
        pGame->board.counts[squareIdx] > 0
        && "Cannot pick up empty stack"
    );

    int const boardWidth = pGame->board.width;
    int stoneCount = pGame->board.counts[squareIdx];

    //* INFO: [Rule] StackBuffer stone count must cap at boardWidth
    stoneCount = ( stoneCount > boardWidth ) ? boardWidth : stoneCount;

    assert(
        stoneCount <= boardWidth
        && "Stone count must be smaller than board witdh"
    );

    int topStoneIdx = squareToStackIndex(
                          squareIdx,
                          pGame->board.stackCapacity
                      )
                      + ( pGame->board.counts[squareIdx] - 1 );

    setBufferStoneType(
        &pGame->stackBuffer,
        pGame->board.types[squareIdx]
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

    StoneType const stackType = pGame->board.types[squareIdx];

    //* INFO: [Rule] No stone can be put onto capstone
    assert(
        stackType != STONE_TYPE_CAP
        && "No stone can be placed onto capstone"
    );

    StoneType const droppedStoneType =
        //
        ( pGame->stackBuffer.count <= 1 )
            ? pGame->stackBuffer.type
            : STONE_TYPE_FLAT;

    //* INFO: [Rule] Capstone can flatten standing stones
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

void undo( Game* const pGame )
{
    switch ( pGame->history.actions[pGame->history.lastActionIdx].count )
    {
        default:
        {
            assert( !"Missing case" );
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
    switch ( pGame->history.actions[pGame->history.lastActionIdx].count )
    {
        default:
        {
            assert( !"Missing case" );
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

