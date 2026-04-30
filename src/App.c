#include "App.h"

#include "ActionTypeId.h"
#include "AppStateId.h"
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
        .state = APP_STATE_FIRST_TURN,
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

    switch ( pApp->state )
    {
        default:
        case APP_STATE_NORMAL_TURN:
        {
            handleAppStateNormalTurn( pApp );

            return;
        }

        case APP_STATE_FIRST_TURN:
        {
            /// Prepare first turn: WHITE places BLACK
            pApp->game.activePlayer = PLAYER_WHITE;
            pApp->command.playerId = PLAYER_BLACK;
            pApp->command.actionType = ACTION_TYPE_PLACE;

            handleAppStateNormalTurn( pApp );

            if ( isTurnComplete( pApp ) )
            {
                pApp->state = APP_STATE_SECOND_TURN;
            }

            return;
        }

        case APP_STATE_SECOND_TURN:
        {
            /// Prepare second turn: BLACK places WHITE
            pApp->game.activePlayer = PLAYER_BLACK;
            pApp->command.playerId = PLAYER_WHITE;
            pApp->command.actionType = ACTION_TYPE_PLACE;

            handleAppStateNormalTurn( pApp );

            if ( isTurnComplete( pApp ) )
            {
                pApp->state = APP_STATE_NORMAL_TURN;
            }

            return;
        }
    }
}

void handleAppStateNormalTurn( App* const pApp )
{
    handleInput( pApp );

    updateApp( pApp );

    renderDynamic( pApp );
}

void handleInput( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    pollInput( &pApp->inputBuffer );

    handleGlobalInput( pApp );

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

    if ( !updateGame( pApp ) )
    {
        return;
    };

    updateCommandPostEvent( &pApp->command );

    if ( isTurnComplete( pApp ) )
    {
        prepareNextTurn( pApp );
    }
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

bool isTurnComplete( App const* const pApp )
{
    return pApp->command.state == STATE_GET_ACTION_TYPE;
}

void prepareNextTurn( App* const pApp )
{
    prepareGame( &pApp->game );
    prepareCommand(
        &pApp->command,
        pApp->game.activePlayer
    );
}
