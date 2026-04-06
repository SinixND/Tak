#include "Redo.h"

#include "Game.h"
#include <assert.h>

void redo( App* const pApp )
{
    History const* const pHistory = &pApp->history;

    assert(
        pHistory->redoCount > 0
        && "Nothing to redo"
    );

    switch ( pHistory->records[pHistory->lastRecordIdx + 1].actionType )
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
    History* const pHistory = &pApp->history;
    Game* const pGame = &pApp->game;

    assert(
        pHistory->redoCount > 0 && "Nothing to redo"
    );

    HistoryRecord const nextRecord = pHistory->records[pHistory->lastRecordIdx + 1];

    placeStone(
        pGame,
        nextRecord.playerId,
        nextRecord.squareIdx,
        nextRecord.stoneType
    );

    //* Adjust history
    redoHistory( &pApp->history );
}

void redoLiftStack( App* const pApp )
{
    History* const pHistory = &pApp->history;
    Game* const pGame = &pApp->game;

    assert(
        pHistory->redoCount > 0 && "Nothing to redo"
    );

    HistoryRecord const nextRecord = pHistory->records[pHistory->lastRecordIdx + 1];

    liftStack(
        pGame,
        nextRecord.squareIdx
    );

    //* Adjust history
    redoHistory( &pApp->history );
}

void redoDropStone( App* const pApp )
{
    History* const pHistory = &pApp->history;
    Game* const pGame = &pApp->game;

    assert(
        pHistory->redoCount > 0 && "Nothing to redo"
    );

    HistoryRecord const nextRecord = pHistory->records[pHistory->lastRecordIdx + 1];

    dropStone(
        pGame,
        nextRecord.squareIdx
    );

    //* Adjust history
    redoHistory( &pApp->history );
}

