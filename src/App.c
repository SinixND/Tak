#include "App.h"

#include "BackendInterface.h"
#include "Command.h"
#include "Engine.h"
#include "Event.h"
#include "Game.h"
#include "InputBuffer.h"
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
        .event = newEvent(),
        .command = newCommand(),
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
    renderStatic( pApp );

    loopBackend( pApp );
}

void closeApp( void )
{
    closeBackend();
}

void updateFrame( App* const pApp )
{
    //* Input
    pollInput( &pApp->inputBuffer );

    //* Update
    updateApp( pApp );

    //* Render
    // WARN: Remove
    renderDynamic( pApp );
}

void updateApp( App* const pApp )
{
    handleGlobalInput( pApp );

    buildCommand( pApp );
}

