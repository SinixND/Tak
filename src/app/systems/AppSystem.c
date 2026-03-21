#include "AppSystem.h"

#include "ActionType.h"
#include "App.h"
#include "AppState.h"
#include "DirectionId.h"
#include "FileId.h"
#include "GameEvent.h"
#include "GameSystem.h"
#include "InputBufferSystem.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneType.h"
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

    app.inputBuffer.gameEvent.stonePlayerId = PLAYER_BLACK;
    app.inputBuffer.gameEvent.actionType = ACTION_TYPE_PLACE;
    app.inputBuffer.gameEvent.stoneType = STONE_TYPE_FLAT;

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

        case STATE_UPDATE_GAME:
        {
            updateStateUpdateGame( app );
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

    appendToCurrentInput(
        app->inputBuffer.currentInput,
        &app->inputBuffer.inputLength,
        FILE_CHARS[app->inputBuffer.gameEvent.fileX]
    );

    //* Change state
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

    appendToCurrentInput(
        app->inputBuffer.currentInput,
        &app->inputBuffer.inputLength,
        RANK_CHARS[app->inputBuffer.gameEvent.rankY]
    );

    //* Set inputBuffer for first turn
    app->inputBuffer.gameEvent.actionType = ACTION_TYPE_PLACE;
    app->inputBuffer.gameEvent.stonePlayerId = PLAYER_BLACK;
    app->inputBuffer.gameEvent.stoneType = STONE_TYPE_FLAT;

    //* Update game without changing state to avoid unnecessary input polling
    updateStateUpdateGame( app );

    resetCurrentInput( &app->inputBuffer );

    //* Change state
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

    appendToCurrentInput(
        app->inputBuffer.currentInput,
        &app->inputBuffer.inputLength,
        FILE_CHARS[app->inputBuffer.gameEvent.fileX]
    );

    //* Change state
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

    appendToCurrentInput(
        app->inputBuffer.currentInput,
        &app->inputBuffer.inputLength,
        RANK_CHARS[app->inputBuffer.gameEvent.rankY]
    );

    //* Set inputBuffer for second turn
    app->inputBuffer.gameEvent.actionType = ACTION_TYPE_PLACE;
    app->inputBuffer.gameEvent.stonePlayerId = PLAYER_WHITE;
    app->inputBuffer.gameEvent.stoneType = STONE_TYPE_FLAT;

    //* Update game without separate state to avoid input polling
    updateStateUpdateGame( app );

    resetCurrentInput( &app->inputBuffer );

    //* Change state
    app->state = STATE_CHOOSE_ACTION;
}

void updateStateChooseAction( App* const app )
{
    //* Keep state on invalid input
    if ( !parseInputForAction( &app->inputBuffer ) )
    {
        return;
    }

    //* Reset on beginning of new turn to allow renderer
    //* to see input at end of turn
    resetCurrentInput( &app->inputBuffer );

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

    //* Update game without separate state to avoid input polling
    updateStateUpdateGame( app );

    //* Update state
    app->state
        = ( app->inputBuffer.currentInput[0]
            == ACTION_TYPE_CHARS[ACTION_TYPE_PLACE] )
              ? STATE_CHOOSE_ACTION
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
    if ( app->inputBuffer.gameEvent.droppedCount < app->inputBuffer.gameEvent.liftCount )
    {
        return;
    }

    //* Update game without separate state to avoid input polling
    updateStateUpdateGame( app );

    //* Update state
    app->state = STATE_CHOOSE_ACTION;
}

void appendToCurrentInput(
    char* currentInput,
    int8_t* const inputLength,
    char const ch
)
{
    currentInput[*inputLength] = ch;

    ++( *inputLength );
}

void updateStateUpdateGame( App* const app )
{
    //* Update game
    //* TODO: Implement rules
    switch ( app->inputBuffer.gameEvent.actionType )
    {
        default:
        {
            assert( !"No valid action type to update game with" );

            return;
        }

        case ACTION_TYPE_PLACE:
        {
            placeStone(
                &app->game,
                app->inputBuffer.gameEvent.stonePlayerId,
                app->inputBuffer.gameEvent.fileX,
                app->inputBuffer.gameEvent.rankY,
                app->inputBuffer.gameEvent.stoneType
            );

            endTurn( app );

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            liftStack(
                &app->game,
                app->inputBuffer.gameEvent.fileX,
                app->inputBuffer.gameEvent.rankY
            );

            return;
        }

        case ACTION_TYPE_DROP:
        {
            int const dir = (int)app->inputBuffer.gameEvent.direction;

            int const offsetX = !( dir % 2 )
                                * ( dir - 3 );

            int const offsetY = ( dir % 2 )
                                * ( dir - 2 );

            int const dropsDone = app->inputBuffer.gameEvent.dropsDone;

            for ( int n = 0; n < dropsDone; ++n )
            {
                int const dropCount = app->inputBuffer.gameEvent.dropCounts[n];

                for ( int m = 0; m < dropCount; ++m )
                {
                    dropStone(
                        &app->game,
                        app->inputBuffer.gameEvent.fileX + offsetX,
                        app->inputBuffer.gameEvent.rankY + offsetY
                    );
                }
            }

            endTurn( app );

            return;
        }
    }
}

void endTurn( App* const app )
{
    //* End turn, change active player
    app->game.activePlayer
        = ( app->game.activePlayer == PLAYER_WHITE )
              ? PLAYER_BLACK
              : PLAYER_WHITE;

    //* Reset input buffer
    app->inputBuffer = newInputBuffer();

    //* Set first state of new turn
    app->state = STATE_CHOOSE_ACTION;
}
