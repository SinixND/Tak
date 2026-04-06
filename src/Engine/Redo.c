#include "Redo.h"

#include "PositionSystem.h"
#include <assert.h>

void redo( App* const pApp )
{
    assert(
        pApp->history.redoCount > 0
        && "Nothing to redo"
    );

    switch ( pApp->history.records[pApp->history.lastRecordIdx + 1].actionType )
    {
        default:
        {
            assert( !"Missing redo case" );
            break;
        }

        case ACTION_TYPE_PLACE:
        {
            redoPlaceStone( pApp );

            break;
        }

        case ACTION_TYPE_LIFT:
        {
            redoLiftStack( pApp );

            break;
        }

        case ACTION_TYPE_DROP:
        {
            redoDropStone( pApp );
            break;
        }
    }
}

void redoPlaceStone( App* const pApp )
{
    assert(
        pApp->history.redoCount > 0 && "Nothing to redo"
    );

    HistoryRecord const nextAction = pApp->history.records[pApp->history.lastRecordIdx + 1];

    int const squareIdx = positionToSquare(
        nextAction.fileX,
        nextAction.rankY,
        pApp->game.board.width
    );

    //* INFO: [Rule] Can only place on empty squares
    assert(
        pApp->game.board.stoneCounts[squareIdx] == 0
        && "Can only place on empty square"
    );

    takeFromReserves(
        &pApp->game.reserves,
        nextAction.playerId,
        nextAction.stoneType
    );

    putOntoStack(
        &pApp->game.board,
        nextAction.playerId,
        nextAction.fileX,
        nextAction.rankY,
        nextAction.stoneType
    );

    //* Adjust history
    redoHistory( &pApp->history );
}

void redoLiftStack( App* const pApp )
{
    assert(
        pApp->history.redoCount > 0 && "Nothing to redo"
    );

    HistoryRecord const nextAction = pApp->history.records[pApp->history.lastRecordIdx + 1];

    int const squareIdx = positionToSquare(
        nextAction.fileX,
        nextAction.rankY,
        pApp->game.board.width
    );

    assert(
        pApp->game.board.stoneCounts[squareIdx] > 0
        && "Cannot pick up empty stack"
    );

    resetBuffer(
        &pApp->game.stackBuffer,
        nextAction.stoneType
    );

    //* Add stones to buffer
    int const topStoneIdx
        = squareToStackIndex(
              squareIdx,
              pApp->game.board.stackCapacity
          )
          + ( pApp->game.board.stoneCounts[squareIdx] - 1 );

    for ( int i = 0; i < nextAction.stoneCount; ++i )
    {
        appendToBuffer(
            &pApp->game.stackBuffer,
            pApp->game.board.stoneIds[topStoneIdx - i]
        );
    }

    //* Remove stones from stack
    takeFromStack(
        &pApp->game.board,
        nextAction.fileX,
        nextAction.rankY,
        nextAction.stoneCount
    );

    //* Adjust history
    redoHistory( &pApp->history );
}

void redoDropStone( App* const pApp )
{
    assert(
        pApp->history.redoCount > 0 && "Nothing to redo"
    );

    HistoryRecord const nextAction = pApp->history.records[pApp->history.lastRecordIdx + 1];

    putOntoStack(
        &pApp->game.board,
        nextAction.playerId,
        nextAction.fileX,
        nextAction.rankY,
        nextAction.stoneType
    );

    dropFromBuffer( &pApp->game.stackBuffer );

    //* Adjust history
    redoHistory( &pApp->history );
}

