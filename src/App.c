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
#include "PlatformInterface.h"
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
        .uiData = newUIData(),
    };

    app.prompts = newPrompts( &app.inputBuffer.mappings );

    return app;
}

void setupApp( App* const pApp )
{
    setupBackend( &pApp->uiData );
}

void runApp( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    render( pApp );

    /// Run loop
    loop( pApp );
}

void closeApp( App* const pApp )
{
    closeBackend( &pApp->uiData );
}

void updateFrame( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    switch ( pApp->state )
    {
        case APP_STATE_CHOOSE_BOARD_SIZE:
        {
            getInput( pApp );

            if ( !setBoardSize(
                     &pApp->game,
                     &pApp->inputBuffer
                 ) )
            {
                break;
            }

            /// Prepare first turn: WHITE places BLACK
            pApp->game.activePlayer = PLAYER_WHITE;
            pApp->command.playerId = PLAYER_BLACK;
            pApp->command.actionType = ACTION_TYPE_PLACE;
            pApp->command.stoneType = STONE_TYPE_FLAT;
            pApp->command.state = COMMAND_STATE_GET_FILE_X;

            pApp->state = APP_STATE_FIRST_TURN;

            break;
        }

        case APP_STATE_FIRST_TURN:
        {
            if (
                !pApp->shouldClose
                && !isTurnComplete( pApp )
            )
            {
                progressTurn( pApp );

                break;
            }

            /// Place additional stone for two-stack opening
            placeStone(
                &pApp->game,
                pApp->history.records[1].Data.place.playerId,
                pApp->history.records[1].Data.place.squareIdx,
                STONE_TYPE_FLAT
            );

            /// Prepare second turn: BLACK places WHITE
            pApp->game.activePlayer = PLAYER_BLACK;
            pApp->command.playerId = PLAYER_WHITE;
            pApp->command.actionType = ACTION_TYPE_PLACE;
            pApp->command.stoneType = STONE_TYPE_FLAT;
            pApp->command.state = COMMAND_STATE_GET_FILE_X;

            pApp->state = APP_STATE_SECOND_TURN;

            break;
        }

        case APP_STATE_SECOND_TURN:
        {
            if (
                !pApp->shouldClose
                && !isTurnComplete( pApp )
            )
            {
                progressTurn( pApp );

                break;
            }

            pApp->state = APP_STATE_NORMAL_TURN;

            break;
        }

        case APP_STATE_NORMAL_TURN:
        {
            progressTurn( pApp );

            break;
        }

        case APP_STATE_TURN_UNDO:
        {
            undoTurn(
                &pApp->history,
                &pApp->game
            );

            /// Reset command
            pApp->command = newCommand( pApp->game.activePlayer );

            pApp->state = APP_STATE_NORMAL_TURN;

            updateScore( &pApp->game );

            break;
        }

        case APP_STATE_TURN_REDO:
        {
            redoTurn(
                &pApp->history,
                &pApp->game
            );

            if ( isGameOver( pApp ) )
            {
                pApp->state = APP_STATE_GAME_END;

                break;
            }

            /// Reset command
            pApp->command = newCommand( pApp->game.activePlayer );

            pApp->state = APP_STATE_NORMAL_TURN;

            updateScore( &pApp->game );

            break;
        }

        case APP_STATE_TURN_RESET:
        {
            resetTurn(
                &pApp->command,
                &pApp->history,
                &pApp->game
            );

            /// Reset command
            pApp->command = newCommand( pApp->game.activePlayer );

            pApp->state = APP_STATE_NORMAL_TURN;

            updateScore( &pApp->game );

            break;
        }

        case APP_STATE_GAME_END:
        {
            getInputFromUser( &pApp->inputBuffer );
            handleGlobalInput( pApp );

            break;
        }

        default:
        {
            assert( !"App state invalid" );
            return;
        }
    }

    render( pApp );
}

void progressTurn( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    /// Input
    if ( !autocompleteCommand(
             &pApp->command,
             &pApp->game
         ) )
    {
        getInput( pApp );

        processInput( pApp );
    };

    /// Action
    updateApp( pApp );
}

// NOTE: Only required as long as simulation is used here
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

    getInputFromUser( &pApp->inputBuffer );
}

void processInput( App* const pApp )
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

    if ( !isCommandReadyForEvent( &pApp->command ) )
    {
        return false;
    }

    buildEvent(
        &pApp->event,
        &pApp->command,
        pApp->game.board.size
    );

    recordEvent(
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

    return pApp->command.state == COMMAND_STATE_GET_FIRST_INPUT;
}

bool isGameOver( App* const pApp )
{
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

            return true;
        }
    }

    return false;
}

void handleTurnEnd( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    updateScore( &pApp->game );

    recordCommand(
        &pApp->history,
        &pApp->command,
        &pApp->game
    );

    if ( isGameOver( pApp ) )
    {
        return;
    }

    updateGamePostEvent( &pApp->game );

    /// Reset command for next turn
    pApp->command = newCommand(
        pApp->game.activePlayer
    );
}
