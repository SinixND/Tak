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
#include "Simulation.h"
#include "StoneTypeId.h"
#include <assert.h>
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
        .simulation = newSimulation(),
        .command = newCommand( PLAYER_BLACK ),
        .event = newEvent(),
        .shouldClose = false,
    };

    app.prompts = newPrompts( &app.inputBuffer.keymap );

    return app;
}

void setupApp( void )
{
    setupBackend();
}

void runApp( App* const pApp )
{
    renderStatic( pApp );

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
            progressTurn( pApp );

            return;
        }

        case APP_STATE_FIRST_TURN:
        {
            /// Prepare first turn: WHITE places BLACK
            pApp->game.activePlayer = PLAYER_WHITE;
            pApp->command.playerId = PLAYER_BLACK;
            pApp->command.actionType = ACTION_TYPE_PLACE;
            pApp->command.stoneType = STONE_TYPE_FLAT;
            pApp->command.state = STATE_GET_FILE_X;

            /// Update altered UI
            renderDynamic( pApp );

            while (
                !pApp->shouldClose
                && !isTurnComplete( pApp )
            )
            {
                progressTurn( pApp );
            }

            pApp->state = APP_STATE_SECOND_TURN;

            return;
        }

        case APP_STATE_SECOND_TURN:
        {
            /// Prepare second turn: BLACK places WHITE
            pApp->game.activePlayer = PLAYER_BLACK;
            pApp->command.playerId = PLAYER_WHITE;
            pApp->command.actionType = ACTION_TYPE_PLACE;
            pApp->command.stoneType = STONE_TYPE_FLAT;
            pApp->command.state = STATE_GET_FILE_X;

            /// Update altered UI
            renderDynamic( pApp );

            while (
                !pApp->shouldClose
                && !isTurnComplete( pApp )
            )
            {
                progressTurn( pApp );
            }

            pApp->state = APP_STATE_NORMAL_TURN;

            return;
        }
    }
}

void progressTurn( App* const pApp )
{
    if ( !autocompleteCommand(
             &pApp->command,
             &pApp->game
         ) )
    {
        getInput( pApp );

        handleInput( pApp );
    };

    updateApp( pApp );

    renderDynamic( pApp );
}

// NOTE: Only reqqired as long as simulation is used here
void getInput( App* const pApp )
{
    if ( simulateInput(
             &pApp->inputBuffer,
             &pApp->simulation
         ) )
    {
        return;
    }

    pollInput( &pApp->inputBuffer );
}

void handleInput( App* const pApp )
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
}

void updateApp( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

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
