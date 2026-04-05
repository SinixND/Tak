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

