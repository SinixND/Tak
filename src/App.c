#include "App.h"

#include "ActionTypeId.h"
#include "AppStateId.h"
#include "BackendInterface.h"
#include "Command.h"
#include "CommandStateId.h"
#include "CommandValidation.h"
#include "Engine.h"
#include "Event.h"
#include "Game.h"
#include "GameConstants.h"
#include "GameEnd.h"
#include "History.h"
#include "InputBuffer.h"
#include "InputParsing.h"
#include "InputSystem.h"
#include "PlatformInterface.h"
#include "PlayerId.h"
#include "Prompts.h"
#include "Simulation.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

void updateStateChooseBoardSize( App* const pApp );
void updateStateFirstTurn( App* const pApp );
void updateStateSecondTurn( App* const pApp );
void updateStateNormalTurn( App* const pApp );
void updateStateUndoTurn( App* const pApp );
void updateStateRedoTurn( App* const pApp );
void updateStateResetTurn( App* const pApp );
void updateStateGameEnd( App* const pApp );

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

    render( pApp );

    switch ( pApp->state )
    {
        case APP_STATE_CHOOSE_BOARD_SIZE:
        {
            updateStateChooseBoardSize( pApp );

            return;
        }

        case APP_STATE_FIRST_TURN:
        {
            updateStateFirstTurn( pApp );

            return;
        }

        case APP_STATE_SECOND_TURN:
        {
            updateStateSecondTurn( pApp );

            return;
        }

        case APP_STATE_NORMAL_TURN:
        {
            updateStateNormalTurn( pApp );

            return;
        }

        case APP_STATE_TURN_UNDO:
        {
            updateStateUndoTurn( pApp );

            return;
        }

        case APP_STATE_TURN_REDO:
        {
            updateStateRedoTurn( pApp );

            return;
        }

        case APP_STATE_TURN_RESET:
        {
            updateStateResetTurn( pApp );

            return;
        }

        case APP_STATE_GAME_END:
        {
            updateStateGameEnd( pApp );

            return;
        }

        default:
        {
            assert( !"App state invalid" );
            return;
        }
    }
}

void updateStateChooseBoardSize( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    getInput( pApp );

    /// Check for Quit input
    if ( getCommandId(
             &pApp->inputBuffer,
             CONTEXT_GLOBAL
         )
         == COMMAND_QUIT )
    {
        pApp->shouldClose = true;

        return;
    }

    if ( !setBoardSize(
             &pApp->game,
             &pApp->inputBuffer
         ) )
    {
        return;
    }

    /// Prepare first turn: WHITE places BLACK
    pApp->game.activePlayer = PLAYER_WHITE;
    pApp->command.playerId = PLAYER_BLACK;
    pApp->command.actionType = ACTION_TYPE_PLACE;
    pApp->command.stoneType = STONE_TYPE_FLAT;
    pApp->command.state = COMMAND_STATE_GET_POSITION;

    pApp->state = APP_STATE_FIRST_TURN;
}

void updateStateFirstTurn( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    /// Input
    getInput( pApp );

    /// Check for Quit input
    if ( getCommandId(
             &pApp->inputBuffer,
             CONTEXT_GLOBAL
         )
         == COMMAND_QUIT )
    {
        pApp->shouldClose = true;

        return;
    }

    /// Build command
    Command command = pApp->command;

    /// Set context-dependent command value from input
    if ( !parsePositionInputToCommand(
             &command,
             &pApp->inputBuffer,
             pApp->game.board.size
         ) )
    {
        return;
    }

    /// Validate command against game
    if ( !validateCommandPosition(
             &command,
             &pApp->game
         ) )
    {
        /// Reset position
        pApp->command.fileX = FILE_NONE;
        pApp->command.rankY = RANK_NONE;

        return;
    }

    /// Copy temp command to original
    pApp->command = command;

    /// Action
    if ( !isCommandReadyForEvent( &pApp->command ) )
    {
        return;
    }

    buildEventFromCommand(
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

    /// Post game update
    updateScore( &pApp->game );

    recordCommand(
        &pApp->history,
        &pApp->command,
        &pApp->game
    );

    changeActivePlayer( &pApp->game );

    /// Reset command for next turn
    pApp->command = newCommand(
        pApp->game.activePlayer
    );

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
    pApp->command.state = COMMAND_STATE_GET_POSITION;

    pApp->state = APP_STATE_SECOND_TURN;
}

void updateStateSecondTurn( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    /// Input
    getInput( pApp );

    /// Check for Quit input
    if ( getCommandId(
             &pApp->inputBuffer,
             CONTEXT_GLOBAL
         )
         == COMMAND_QUIT )
    {
        pApp->shouldClose = true;

        return;
    }

    /// Build command
    Command command = pApp->command;

    /// Set context-dependent command value from input
    if ( !parsePositionInputToCommand(
             &command,
             &pApp->inputBuffer,
             pApp->game.board.size
         ) )
    {
        return;
    }

    /// Validate command against game
    if ( !validateCommandPosition(
             &command,
             &pApp->game
         ) )
    {
        /// Reset position
        pApp->command.fileX = FILE_NONE;
        pApp->command.rankY = RANK_NONE;

        return;
    }

    /// Copy temp command to original
    pApp->command = command;

    /// Action
    if ( !isCommandReadyForEvent( &pApp->command ) )
    {
        return;
    }

    buildEventFromCommand(
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

    /// Post game update
    updateScore( &pApp->game );

    recordCommand(
        &pApp->history,
        &pApp->command,
        &pApp->game
    );

    changeActivePlayer( &pApp->game );

    /// Reset command for next turn
    pApp->command = newCommand(
        pApp->game.activePlayer
    );

    pApp->state = APP_STATE_NORMAL_TURN;
}

void updateStateNormalTurn( App* const pApp )
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
        /// Input
        getInput( pApp );

        handleGlobalInput( pApp );

        /// Temporary command
        Command command = pApp->command;

        /// Set context-dependent command value from input
        if ( !updateCommandFromInput(
                 &command,
                 &pApp->inputBuffer,
                 pApp->game.board.size
             ) )
        {
            return;
        }

        /// Validate input against game
        if ( !validateCommand(
                 &command,
                 &pApp->game
             ) )
        {
            /// Reset original command position if invalid
            if ( command.state == COMMAND_STATE_DEFAULT )
            {
                pApp->command.fileX = FILE_NONE;
                pApp->command.rankY = RANK_NONE;
            }

            /// Keep buffered stone count
            pApp->command.bufferedDropCount = command.bufferedDropCount;

            return;
        }

        /// Update command state
        setNextCommandState(
            &command,
            &pApp->game
        );

        /// Copy temp command to original
        pApp->command = command;
    };

    /// Action
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

void updateStateUndoTurn( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    undoTurn(
        &pApp->history,
        &pApp->game
    );

    /// Reset command
    pApp->command = newCommand( pApp->game.activePlayer );

    pApp->state = APP_STATE_NORMAL_TURN;

    updateScore( &pApp->game );
}

void updateStateRedoTurn( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    redoTurn(
        &pApp->history,
        &pApp->game
    );

    if ( isGameOver( pApp ) )
    {
        pApp->state = APP_STATE_GAME_END;

        return;
    }

    /// Reset command
    pApp->command = newCommand( pApp->game.activePlayer );

    pApp->state = APP_STATE_NORMAL_TURN;

    updateScore( &pApp->game );
}

void updateStateResetTurn( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    resetTurn(
        &pApp->command,
        &pApp->history,
        &pApp->game
    );

    /// Reset command
    pApp->command = newCommand( pApp->game.activePlayer );

    pApp->state = APP_STATE_NORMAL_TURN;

    updateScore( &pApp->game );
}

void updateStateGameEnd( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    getInputFromUser( &pApp->inputBuffer );
    handleGlobalInput( pApp );
}

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
        return;
    }

    getInputFromUser( &pApp->inputBuffer );
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

    buildEventFromCommand(
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

    return pApp->command.state == COMMAND_STATE_DEFAULT;
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

    changeActivePlayer( &pApp->game );

    /// Reset command for next turn
    pApp->command = newCommand(
        pApp->game.activePlayer
    );
}
