#include "AppSystem.h"

#include "ActionType.h"
#include "App.h"
#include "AppState.h"
#include "DirectionId.h"
#include "GameSystem.h"
#include "InputBufferSystem.h"
#include <assert.h>
#include <stdint.h>

//* Choose backend
#ifdef BACKEND_NCURSES
#include "ContextSystem_NCurses.h"
#endif

App newApp( int const boardWidth )
{
    App app = {
        .game = newGame( boardWidth ),
        .inputBuffer = newInputBuffer(),
        .state = STATE_FIRST_TURN_CHOOSE_FILE_X,
        .shoudClose = false,
    };

    return app;
}

void initApp( void )
{
    initBackend();
}

void deinitApp( void )
{
    deinitBackend();
}

void updateApp( App* const app )
{
    handleGlobalInput( app );
    updateState( app );
}

void handleGlobalInput( App* const app )
{
    //* Conditionally terminate by
    //* changing main while loop condition
    app->shoudClose
        = ( app->inputBuffer.lastInput == INPUT_Q )
              ? true
              : false;
}

void updateState( App* const app )
{
    switch ( app->state )
    {
        default:
        {
            assert( !"Invalid appState" );
        }

        case STATE_FIRST_TURN_CHOOSE_FILE_X:
        {
            updateStateFirstTurnChooseFileX( app );
            return;
        }

        case STATE_FIRST_TURN_CHOOSE_RANK_Y:
        {
            updateStateFirstTurnChooseRankY( app );
            return;
        }

        case STATE_SECOND_TURN_CHOOSE_FILE_X:
        {
            updateStateSecondTurnChooseFileX( app );
            return;
        }

        case STATE_SECOND_TURN_CHOOSE_RANK_Y:
        {
            updateStateSecondTurnChooseRankY( app );
            return;
        }

        case STATE_CHOOSE_ACTION:
        {
            updateStateChooseAction( app );
            return;
        }

        case STATE_CHOOSE_FILE_X:
        {
            updateStateChooseFileX( app );
            return;
        }

        case STATE_CHOOSE_RANK_Y:
        {
            updateStateChooseRankY( app );
            return;
        }

        case STATE_CHOOSE_STONE_TYPE:
        {
            updateStateChooseStoneType( app );
            return;
        }

        case STATE_CHOOSE_DIRECTION:
        {
            updateStateChooseDirection( app );
            return;
        }

        case STATE_CHOOSE_FIRST_DROP_AMOUNT:
        {
            updateStateChooseFirstDropAmount( app );
            return;
        }

        case STATE_CHOOSE_AMOUNT:
        {
            updateStateChooseAmount( app );
            return;
        }
    }
}

void updateStateFirstTurnChooseFileX( App* const app )
{
    //* White places first black
    //* Keep state on invalid input
    if ( !parseInputForFileX( &app->inputBuffer ) )
    {
        return;
    }

    app->state = STATE_FIRST_TURN_CHOOSE_RANK_Y;
}

void updateStateFirstTurnChooseRankY( App* const app )
{
    //* White places first black
    //* Keep state on invalid input
    if ( !parseInputForRankY( &app->inputBuffer ) )
    {
        return;
    }

    app->state = STATE_SECOND_TURN_CHOOSE_FILE_X;
}

void updateStateSecondTurnChooseFileX( App* const app )
{
    //* Black places first white
    //* Keep state on invalid input
    if ( !parseInputForFileX( &app->inputBuffer ) )
    {
        return;
    }

    app->state = STATE_SECOND_TURN_CHOOSE_RANK_Y;
}

void updateStateSecondTurnChooseRankY( App* const app )
{
    //* Black places first white
    //* Keep state on invalid input
    if ( !parseInputForRankY( &app->inputBuffer ) )
    {
        return;
    }

    app->state = STATE_CHOOSE_ACTION;
}

void updateStateChooseAction( App* const app )
{
    //* Keep state on invalid input
    if ( !parseInputForAction( &app->inputBuffer ) )
    {
        return;
    }

    //* Update current input
    appendToCurrentInput(
        app->inputBuffer.currentInput,
        &app->inputBuffer.inputLength,
        ACTION_TYPE_CHARS[app->inputBuffer.gameEvent.actionType]
    );

    //* Change state
    switch ( app->inputBuffer.gameEvent.actionType )
    {
        default:
        {
            //* Do nothing
            return;
        }

        case ACTION_TYPE_PLACE:
        {
            app->state = STATE_CHOOSE_STONE_TYPE;

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            app->state = STATE_CHOOSE_FILE_X;

            return;
        }
    }
}

void updateStateChooseStoneType( App* const app )
{
    //* Keep state on invalid input
    if ( !parseInputForStoneType( &app->inputBuffer ) )
    {
        return;
    }

    //* Update current input
    appendToCurrentInput(
        app->inputBuffer.currentInput,
        &app->inputBuffer.inputLength,
        STONE_TYPE_CHARS[app->inputBuffer.gameEvent.stoneType]
    );

    //* Update state
    app->state = STATE_CHOOSE_FILE_X;
}

void updateStateChooseFileX( App* const app )
{
    //* Keep state on invalid input
    if ( !parseInputForFileX( &app->inputBuffer ) )
    {
        return;
    }

    //* Update current input
    appendToCurrentInput(
        app->inputBuffer.currentInput,
        &app->inputBuffer.inputLength,
        FILE_CHARS[app->inputBuffer.gameEvent.fileX]
    );

    //* Update state
    app->state = STATE_CHOOSE_RANK_Y;
}

void updateStateChooseRankY( App* const app )
{
    //* Keep state on invalid input
    if ( !parseInputForRankY( &app->inputBuffer ) )
    {
        return;
    }

    //* Update current input
    appendToCurrentInput(
        app->inputBuffer.currentInput,
        &app->inputBuffer.inputLength,
        RANK_CHARS[app->inputBuffer.gameEvent.rankY]
    );

    //* Update state
    app->state
        = ( app->inputBuffer.currentInput[0]
            == ACTION_TYPE_CHARS[ACTION_TYPE_PLACE] )
              ? STATE_UPDATE_GAME
              : STATE_CHOOSE_DIRECTION;
}

void updateStateChooseDirection( App* const app )
{
    //* Keep state on invalid input
    if ( !parseInputForDirection( &app->inputBuffer ) )
    {
        return;
    }

    //* Update current input
    appendToCurrentInput(
        app->inputBuffer.currentInput,
        &app->inputBuffer.inputLength,
        DIRECTION_CHARS[app->inputBuffer.gameEvent.direction]
    );

    //* Update state
    app->state = STATE_CHOOSE_FIRST_DROP_AMOUNT;
}

void updateStateChooseFirstDropAmount( App* const app )
{
    //* Keep state on invalid input
    if ( !parseInputForFirstDropAmount( &app->inputBuffer ) )
    {
        return;
    }

    //* Update current input
    appendToCurrentInput(
        app->inputBuffer.currentInput,
        &app->inputBuffer.inputLength,
        app->inputBuffer.gameEvent.dropCounts[app->inputBuffer.gameEvent.dropsDone - 1] + '0'
    );

    //* Update state
    app->state = STATE_CHOOSE_AMOUNT;
}

void updateStateChooseAmount( App* const app )
{
    //* Keep state on invalid input
    if ( !parseInputForAmount( &app->inputBuffer ) )
    {
        return;
    }

    //* Update current input
    appendToCurrentInput(
        app->inputBuffer.currentInput,
        &app->inputBuffer.inputLength,
        app->inputBuffer.gameEvent.dropCounts[app->inputBuffer.gameEvent.dropsDone - 1] + '0'
    );

    //* Check if all dropped
    if ( app->inputBuffer.gameEvent.droppedCount >= app->inputBuffer.gameEvent.liftCount )
    {
        app->state = STATE_UPDATE_GAME;
    }
}

//* TODO:
// void updateStateUpdateGame( App* const app )
// {
//     //* Reset current input
//
// }

void appendToCurrentInput(
    char* currentInput,
    int8_t* const inputLength,
    char const ch
)
{
    currentInput[*inputLength] = ch;

    ++( *inputLength );
}
