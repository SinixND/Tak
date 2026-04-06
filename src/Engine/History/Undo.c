#include "Undo.h"

#include "App.h"
#include "Game.h"
#include "Record.h"
#include "StackBuffer.h"
#include "StoneTypeId.h"
#include <assert.h>

void undo( App* const pApp )
{
    History const* const pHistory = &pApp->history;

    assert(
        pHistory->lastRecordIdx >= 0
        && "Nothing to undo"
    );

    switch ( pHistory->records[pHistory->lastRecordIdx].actionType )
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
    Record const lastRecord = pApp->history.records[pApp->history.lastRecordIdx];

    takeStone(
        &pApp->game,
        lastRecord.squareIdx
    );

    //* Adjust history
    undoHistory( &pApp->history );
}

void undoLiftStack( App* const pApp )
{
    Record const lastRecord = pApp->history.records[pApp->history.lastRecordIdx];

    dropStack(
        &pApp->game,
        lastRecord.squareIdx
    );

    //* Adjust history
    undoHistory( &pApp->history );
}

void undoDropStone( App* const pApp )
{
    Record const lastRecord = pApp->history.records[pApp->history.lastRecordIdx];

    liftStone(
        &pApp->game,
        lastRecord.squareIdx,
        lastRecord.flattened
    );

    //* Adjust history
    undoHistory( &pApp->history );
}

