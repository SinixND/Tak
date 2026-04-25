#include "App.h"

#include "BackendInterface.h"
#include "Command.h"
#include "Engine.h"
#include "Event.h"
#include "Game.h"
#include "InputBuffer.h"
#include "InputSystem.h"
#include "PlayerId.h"
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
        .command = newCommand( PLAYER_BLACK ),
        .prompt = newPrompt(),
        .shouldClose = false,
    };

    // TODO: Move to first turn handler later
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

    /// Run loop
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

    /// Input
    pApp->inputBuffer.playerId = pApp->game.activePlayer;
    pollInput( &pApp->inputBuffer );

    /// Update
    updateApp( pApp );

    /// Render
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

    // Update prompt
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

    /// Handle turn end
    if ( pApp->command.state != STATE_GET_ACTION_TYPE )
    {
        return;
    }

    endTurn( pApp );
}

void endTurn( App* const pApp )
{
    prepareGame( &pApp->game );
    prepareCommand( &pApp->command );
}
