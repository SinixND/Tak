#include "App.h"

#include "BackendInterface.h"
#include "Command.h"
#include "CommandStateId.h"
#include "Engine.h"
#include "Event.h"
#include "Game.h"
#include "InputBuffer.h"
#include "InputSystem.h"
#include "Prompts.h"
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
        .prompt = newPrompt(),
        .shouldClose = false,
    };

    app.command.state = STATE_GET_FILE_X;
    app.prompt = PROMPTS[app.command.state];

    return app;
}

void setupApp( void )
{
    setupBackend();
}

void runApp( App* const pApp )
{
    renderStatic( pApp );
    renderDynamic( pApp );

    //* Update prompt
    pApp->prompt = PROMPTS[pApp->command.state];

    loopBackend( pApp );
}

void closeApp( void )
{
    closeBackend();
}

void updateFrame( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    //* Input
    pApp->inputBuffer.playerId = pApp->game.activePlayer;
    pollInput( &pApp->inputBuffer );

    //* Update
    updateApp( pApp );

    //* Render
    renderDynamic( pApp );
}

void updateApp( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    handleGlobalInput( pApp );

    buildCommand(
        &pApp->command,
        &pApp->inputBuffer,
        &pApp->game
    );

    //* Update prompt
    pApp->prompt = PROMPTS[pApp->command.state];

    if ( !isCommandComplete( &pApp->command ) )
    {
        return;
    }

    buildEvent(
        &pApp->event,
        &pApp->command,
        pApp->game.board.size
    );

    executeEvent(
        &pApp->game,
        &pApp->event
    );
}

