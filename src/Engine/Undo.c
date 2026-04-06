#include "Undo.h"

#include "App.h"
#include "HistoryRecord.h"
#include "PositionSystem.h"
#include <assert.h>

void undo( App* const pApp )
{
    assert(
        pApp->history.lastRecordIdx >= 0
        && "Nothing to undo"
    );

    switch ( pApp->history.records[pApp->history.lastRecordIdx].actionType )
    {
        default:
        {
            assert( !"Missing undo case" );
            break;
        }

        case ACTION_TYPE_PLACE:
        {
            undoPlaceStone( pApp );
            break;
        }

        case ACTION_TYPE_LIFT:
        {
            undoLiftStack( pApp );
            break;
        }

        case ACTION_TYPE_DROP:
        {
            undoDropStone( pApp );
            break;
        }
    }
}

void undoPlaceStone( App* const pApp )
{
    HistoryRecord const lastRecord = pApp->history.records[pApp->history.lastRecordIdx];

    //* Undo putOnStack
    takeFromStack(
        &pApp->game.board,
        lastRecord.fileX,
        lastRecord.rankY,
        1
    );

    //* Undo takeFromReserves
    returnToReserves(
        &pApp->game.reserves,
        lastRecord.playerId,
        lastRecord.stoneType
    );

    //* Adjust history
    undoHistory( &pApp->history );
}

void undoLiftStack( App* const pApp )
{
    HistoryRecord const lastRecord = pApp->history.records[pApp->history.lastRecordIdx];

    //* Add stones to stack
    for ( int i = 0; i < lastRecord.stoneCount; ++i )
    {
        putOntoStack(
            &pApp->game.board,
            pApp->game.stackBuffer.stoneIds[( lastRecord.stoneCount - 1 ) - i],
            lastRecord.fileX,
            lastRecord.rankY,
            lastRecord.stoneType
        );
    }

    //* Empty buffer
    pApp->game.stackBuffer.stoneCount = 0;

    //* Adjust history
    undoHistory( &pApp->history );
}

void undoDropStone( App* const pApp )
{
    HistoryRecord const lastRecord = pApp->history.records[pApp->history.lastRecordIdx];

    int const squareIdx = positionToSquare(
        lastRecord.fileX,
        lastRecord.rankY,
        pApp->game.board.width
    );

    //* INFO: [Rule] No stone can be put onto capstone
    assert(
        pApp->game.board.stoneCounts[squareIdx] > 0
        && "Cant undo drop from emtpy square"
    );

    appendToBuffer(
        &pApp->game.stackBuffer,
        lastRecord.playerId
    );

    takeFromStack(
        &pApp->game.board,
        lastRecord.fileX,
        lastRecord.rankY,
        lastRecord.stoneCount
    );

    //* Make stackType 'standing' if drop flattened
    pApp->game.board.types[squareIdx]
        = lastRecord.flattened
              ? STONE_TYPE_STANDING
              : STONE_TYPE_FLAT;

    //* Adjust history
    undoHistory( &pApp->history );
}

