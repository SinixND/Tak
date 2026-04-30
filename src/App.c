#include "App.h"

#include "ActionTypeId.h"
#include "BackendInterface.h"
#include "Command.h"
#include "CommandStateId.h"
#include "Engine.h"
#include "Event.h"
#include "Game.h"
#include "InputBuffer.h"
#include "InputSystem.h"
#include "PlayerId.h"
#include "Prompts.h"
#include <assert.h>
#include <ncurses.h>
#include <stdbool.h>

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
    handleInput( pApp );

    /// Update
    updateApp( pApp );

    /// Render
    renderDynamic( pApp );
}

void handleInput( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    // TODO: return bool for early return?
    pollInput( &pApp->inputBuffer );

    handleGlobalInput( pApp );

    // TODO: return bool for conditional app update?
    buildCommand(
        &pApp->command,
        &pApp->inputBuffer,
        &pApp->game
    );
}

void updateApp( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    /// Pre event update
    pApp->prompt = PROMPTS[pApp->command.state];

    /// Update Game
    if ( !updateGame( pApp ) )
    {
        return;
    };

    /// Post event command update
    if ( pApp->command.state == STATE_GET_FIRST_DROP_AMOUNT
         || pApp->command.state == STATE_GET_DROP_AMOUNT )
    {
        ++pApp->command.drops;
        return;
    }

    if ( pApp->command.actionType == ACTION_TYPE_LIFT )
    {
        pApp->command.actionType = ACTION_TYPE_DROP;
    }

    /// Handle turn end
    /// TODO: isTurnComplete();
    if ( pApp->command.state != STATE_GET_ACTION_TYPE )
    {
        return;
    }

    prepareNextTurn( pApp );
}

bool updateGame( App* const pApp )
{
    if ( !isCommandReady( &pApp->command ) )
    {
        return false;
    }

    // TODO: Apply command directly?
    buildEvent(
        &pApp->event,
        &pApp->command,
        pApp->game.board.size
    );

    executeEvent(
        &pApp->game,
        &pApp->event
    );

    return true;
}

void prepareNextTurn( App* const pApp )
{
    prepareGame( &pApp->game );
    prepareCommand( &pApp->command );
}
