#include "App.h"

#include "ActionTypeId.h"
#include "AppStateId.h"
#include "BackendInterface.h"
#include "Command.h"
#include "CommandStateId.h"
#include "Engine.h"
#include "Event.h"
#include "Game.h"
#include "GameConstants.h"
#include "GameEnd.h"
#include "History.h"
#include "InputBuffer.h"
#include "InputSystem.h"
#include "Keymap.h"
#include "PlayerId.h"
#include "Prompts.h"
#include "Simulation.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

App newApp( void )
{
    App app = {
        .state = APP_STATE_CHOOSE_BOARD_SIZE,
        .game = newGame( BOARD_SIZE_DEFAULT ),
        .inputBuffer = newInputBuffer(),
        .simulation = newSimulation(),
        .command = newCommand( PLAYER_BLACK ),
        .event = newEvent(),
        .history = newHistory(),
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
    assert(
        pApp
        && "Pointer is nullptr"
    );

    renderStartScreen();

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
        case APP_STATE_CHOOSE_BOARD_SIZE:
        {
            getInput( pApp );

            if ( !setBoardSize( pApp ) )
            {
                return;
            }

            renderStatic( pApp );

            pApp->state = APP_STATE_FIRST_TURN;

            return;
        }

        case APP_STATE_FIRST_TURN:
        {
            /// Prepare first turn: WHITE places BLACK
            pApp->game.activePlayer = PLAYER_WHITE;
            pApp->command.playerId = PLAYER_BLACK;
            pApp->command.actionType = ACTION_TYPE_PLACE;
            pApp->command.stoneType = STONE_TYPE_FLAT;
            pApp->command.state = COMMAND_STATE_GET_FILE_X;

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
            pApp->command.state = COMMAND_STATE_GET_FILE_X;

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

        case APP_STATE_NORMAL_TURN:
        {
            progressTurn( pApp );

            return;
        }

        case APP_STATE_TURN_UNDO:
        {
            pApp->state = APP_STATE_NORMAL_TURN;

            return;
        }

        case APP_STATE_TURN_REDO:
        {
            pApp->state = APP_STATE_NORMAL_TURN;

            return;
        }

        case APP_STATE_TURN_RESET:
        {
            pApp->state = APP_STATE_NORMAL_TURN;

            return;
        }

        case APP_STATE_GAME_END:
        {
            renderCommandGameEnd( pApp );

            pollInput( &pApp->inputBuffer );
            handleGlobalInput( pApp );

            return;
        }
    }
}

bool setBoardSize( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    switch ( getCommandId(
        &pApp->inputBuffer,
        CONTEXT_SIZE
    ) )
    {
        case COMMAND_3:
        {
            pApp->game = newGame( 3 );

            return true;
        }

        case COMMAND_4:
        {
            pApp->game = newGame( 4 );

            return true;
        }

        case COMMAND_CONFIRM:
        case COMMAND_5:
        {
            pApp->game = newGame( 5 );

            return true;
        }

        case COMMAND_6:
        {
            pApp->game = newGame( 6 );

            return true;
        }

        case COMMAND_7:
        {
            pApp->game = newGame( 7 );

            return true;
        }

        case COMMAND_8:
        {
            pApp->game = newGame( 8 );

            return true;
        }

        default:
            return false;
    }
}

void progressTurn( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

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
    assert(
        pApp
        && "Pointer is nullptr"
    );

    if ( simulateInput(
             &pApp->inputBuffer,
             &pApp->simulation
         ) )
    {
        wait( 10 );
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

    if ( !isTurnComplete( pApp ) )
    {
        return;
    }

    handleTurnEnd( pApp );
}

bool updateGame( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

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

    buildRecord(
        &pApp->history,
        &pApp->event,
        &pApp->game
    );

    executeEvent(
        &pApp->game,
        &pApp->event
    );

    return true;
}

bool isTurnComplete( App const* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    return pApp->command.state == COMMAND_STATE_GET_ACTION_TYPE;
}

void handleTurnEnd( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    updateScore( &pApp->game );

    /// Check if and which player won
    for ( int playerId = 0; playerId < PLAYER_COUNT; ++playerId )
    {
        if (
            isWinConditionMet(
                &pApp->game,
                playerId
            )
        )
        {
            pApp->game.activePlayer = playerId;
            pApp->state = APP_STATE_GAME_END;

            return;
        }
    }

    prepareGame( &pApp->game );
    prepareCommand(
        &pApp->command,
        pApp->game.activePlayer
    );
}
