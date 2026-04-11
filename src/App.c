#include "App.h"

#include "BackendInterface.h"
#include "Game.h"
#include "InputBuffer.h"
#include "InputId.h"
#include "InputSystem.h"
#include <assert.h>
#include <ncurses.h>

App newApp( int const boardSize )
{
    assert(
        ( boardSize >= BOARD_SIZE_MIN
          || !boardSize )
        && "Board size value too small"
    );

    assert(
        ( boardSize <= BOARD_SIZE_MAX )
        && "Board size value too big"
    );

    App app = {
        .game = newGame( boardSize ),
        .inputBuffer = newInputBuffer(),
        .engine = newEngine(),
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
    // WARN: Remove
    mvprintw(
        0,
        0,
        "%c",
        INPUT_CHARS[pApp->inputBuffer.keyboard]
    );
}

