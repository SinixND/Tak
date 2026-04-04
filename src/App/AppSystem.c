#include "AppSystem.h"

#include "GameSystem.h"
#include "InputBufferSystem.h"
#include "InputSystem.h"
#include <assert.h>

//* Choose backend
#ifdef BACKEND_NCURSES
#include "BackendInterface.h"
#endif

App newApp( int const boardWidth )
{
    assert(
        ( boardWidth >= BOARD_WIDTH_MIN
          || !boardWidth )
        && "Board width value too small"
    );

    assert(
        ( boardWidth <= BOARD_WIDTH_MAX )
        && "Board width value too big"
    );

    App app = {
        .game = newGame( boardWidth ),
        .inputBuffer = newInputBuffer(),
        .shouldClose = false,
    };

    return app;
}

void setupApp( void )
{
    setupBackend();
}

void runApp( App* const pApp )
{
    loopBackend( pApp );
}

void closeApp( void )
{
    closeBackend();
}

void updateFrame( App* const pApp )
{
    pollInput( &pApp->inputBuffer );
    handleGlobalInput( pApp );
}

void undo( App* const pApp )
{
    assert(
        pApp->game.history.lastRecordIdx >= 0
        && "Nothing to undo"
    );

    switch ( pApp->game.history.records[pApp->game.history.lastRecordIdx].actionType )
    {
        default:
        {
            assert( !"Missing undo case" );
            break;
        }

        case ACTION_TYPE_PLACE:
        {
            undoPlaceStone( &pApp->game );
            break;
        }

        case ACTION_TYPE_LIFT:
        {
            undoLiftStack( &pApp->game );
            break;
        }

        case ACTION_TYPE_DROP:
        {
            undoDropStone( &pApp->game );
            break;
        }
    }
}

void redo( App* const pApp )
{
    assert(
        pApp->game.history.redoCount > 0
        && "Nothing to redo"
    );

    switch ( pApp->game.history.records[pApp->game.history.lastRecordIdx + 1].actionType )
    {
        default:
        {
            assert( !"Missing redo case" );
            break;
        }

        case ACTION_TYPE_PLACE:
        {
            redoPlaceStone( &pApp->game );

            break;
        }

        case ACTION_TYPE_LIFT:
        {
            redoLiftStack( &pApp->game );

            break;
        }

        case ACTION_TYPE_DROP:
        {
            redoDropStone( &pApp->game );
            break;
        }
    }
}
