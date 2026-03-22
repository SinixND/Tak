#include "AppSystem.h"

#include "ActionType.h"
#include "App.h"
#include "AppState.h"
#include "DirectionId.h"
#include "FileId.h"
#include "GameEvent.h"
#include "GameSystem.h"
#include "InputBuffer.h"
#include "InputBufferSystem.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StatePhase.h"
#include "StoneType.h"
#include <assert.h>
#include <stdbool.h>
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
        .state = STATE_FIRST_TURN,
        .phase = PHASE_GET_FILE_X,
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
    //* NOTE: Maybe extract into separate function later
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
            assert( !"Invalid app state" );
        }

        case STATE_FIRST_TURN:
        {
            handleStateFirstTurn( app );

            return;
        }

        case STATE_SECOND_TURN:
        {
            handleStateSecondTurn( app );

            return;
        }

        case STATE_CHOOSE_ACTION:
        {
            handleStateChooseAction( app );

            return;
        }

        case STATE_PREPARE_EVENT_PLACE:
        {
            handleStatePrepareEventPlace( app );

            return;
        }

        case STATE_PREPARE_EVENT_LIFT:
        {
            handleStatePrepareEventLift( app );

            return;
        }

        case STATE_PREPARE_EVENT_DROP:
        {
            handleStatePrepareEventDrop( app );

            return;
        }

        case STATE_UPDATE_GAME:
        {
            handleStateUpdateGame( app );

            return;
        }

        case STATE_END_TURN:
        {
            handleStateEndTurn( app );

            return;
        }
    }
}

void changeState(
    App* const app,
    AppState const state
)
{
    app->phase = PHASE_NONE;
    app->state = state;
}

void handleStateFirstTurn( App* const app )
{
    switch ( app->phase )
    {
        default:
        {
            app->phase = PHASE_GET_FILE_X;
        }

        case PHASE_GET_FILE_X:
        {
            if ( !handleInputFileX( app ) )
            {
                return;
            }

            app->phase = PHASE_GET_RANK_Y;

            return;
        }

        case PHASE_GET_RANK_Y:
        {
            if ( !handleInputRankY( app ) )
            {
                return;
            }

            //* Prepare game event for first turn
            app->inputBuffer.gameEvent.actionType = ACTION_TYPE_PLACE;
            app->inputBuffer.gameEvent.stonePlayerId = PLAYER_BLACK;
            app->inputBuffer.gameEvent.stoneType = STONE_TYPE_FLAT;

            //* Update game without changing state to default for new turn
            handleStateUpdateGame( app );
            handleStateEndTurn( app );

            changeState(
                app,
                STATE_SECOND_TURN
            );

            app->phase = PHASE_GET_FILE_X;

            return;
        }
    }
}

void handleStateSecondTurn( App* const app )
{
    switch ( app->phase )
    {
        default:
        {
            app->phase = PHASE_GET_FILE_X;
        }

        case PHASE_GET_FILE_X:
        {
            if ( !handleInputFileX( app ) )
            {
                return;
            }

            app->phase = PHASE_GET_RANK_Y;

            return;
        }

        case PHASE_GET_RANK_Y:
        {
            if ( !handleInputRankY( app ) )
            {
                return;
            }

            //* Prepare game event for first turn
            app->inputBuffer.gameEvent.actionType = ACTION_TYPE_PLACE;
            app->inputBuffer.gameEvent.stonePlayerId = PLAYER_WHITE;
            app->inputBuffer.gameEvent.stoneType = STONE_TYPE_FLAT;

            changeState(
                app,
                STATE_UPDATE_GAME
            );

            return;
        }
    }
}

void handleStateChooseAction( App* const app )
{
    if ( !parseInputAction( &app->inputBuffer ) )
    {
        return;
    }

    appendToCurrentCommand(
        &app->inputBuffer,
        ACTION_TYPE_CHARS[app->inputBuffer.gameEvent.actionType]
    );

    appendToCurrentCommand(
        &app->inputBuffer,
        ':'
    );

    //* Change state
    switch ( app->inputBuffer.gameEvent.actionType )
    {
        default:
            return;

        case ACTION_TYPE_PLACE:
        {
            app->state = STATE_PREPARE_EVENT_PLACE;

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            app->state = STATE_PREPARE_EVENT_LIFT;

            return;
        }
    }
}

void handleStatePrepareEventPlace( App* const app )
{
    switch ( app->phase )
    {
        default:
        {
            app->phase = PHASE_GET_STONE_TYPE;
        }

        case PHASE_GET_STONE_TYPE:
        {
            if ( !handleInputStoneType( app ) )
            {
                return;
            }

            app->phase = PHASE_GET_FILE_X;

            return;
        }

        case PHASE_GET_FILE_X:
        {
            if ( !handleInputFileX( app ) )
            {
                return;
            }

            app->phase = PHASE_GET_RANK_Y;

            return;
        }

        case PHASE_GET_RANK_Y:
        {
            if ( !handleInputRankY( app ) )
            {
                return;
            }

            changeState(
                app,
                STATE_UPDATE_GAME
            );

            return;
        }
    }
}
void handleStatePrepareEventLift( App* const app )
{
    switch ( app->phase )
    {
        default:
        {
            app->phase = PHASE_GET_FILE_X;
        }

        case PHASE_GET_FILE_X:
        {
            if ( !handleInputFileX( app ) )
            {
                return;
            }

            app->phase = PHASE_GET_RANK_Y;

            return;
        }

        case PHASE_GET_RANK_Y:
        {
            if ( !handleInputRankY( app ) )
            {
                return;
            }

            app->phase = PHASE_GET_DIRECTION;

            return;
        }

        case PHASE_GET_DIRECTION:
        {
            if ( !handleInputDirection( app ) )
            {
                return;
            }

            changeState(
                app,
                STATE_UPDATE_GAME
            );

            return;
        }
    }
}

void handleStatePrepareEventDrop( App* const app )
{
    switch ( app->phase )
    {
        default:
        {
            app->phase = PHASE_GET_FIRST_DROP_AMOUNT;
        }

        case PHASE_GET_FIRST_DROP_AMOUNT:
        {
            if ( !handleInputFirstDropAmount( app ) )
            {
                return;
            }

            //* Check stones remain to be dropped
            if ( app->inputBuffer.gameEvent.droppedCount < app->inputBuffer.gameEvent.liftCount )
            {
                app->phase = PHASE_GET_DROP_AMOUNT;

                return;
            }

            changeState(
                app,
                STATE_UPDATE_GAME
            );

            return;
        }

        case PHASE_GET_DROP_AMOUNT:
        {
            if ( !handleInputDropAmount( app ) )
            {
                return;
            }

            //* Check stones remain to be dropped
            if ( app->inputBuffer.gameEvent.droppedCount < app->inputBuffer.gameEvent.liftCount )
            {
                return;
            }

            changeState(
                app,
                STATE_UPDATE_GAME
            );

            return;
        }
    }
}

void handleStateUpdateGame( App* const app )
{
    //* TODO: Implement rules

    //* Update game
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

            //* Update state
            app->state = STATE_END_TURN;

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            liftStack(
                &app->game,
                app->inputBuffer.gameEvent.fileX,
                app->inputBuffer.gameEvent.rankY
            );

            //* Set liftCount
            app->inputBuffer.gameEvent.liftCount = app->game.stackBuffer.stoneCount;

            app->state = STATE_PREPARE_EVENT_DROP;

            return;
        }

        case ACTION_TYPE_DROP:
        {
            int const dir = (int)app->inputBuffer.gameEvent.direction;

            int const offsetY
                = !!dir
                  * ( dir % 2 )
                  * ( dir - 2 );

            int const offsetX
                = !!dir
                  * !( dir % 2 )
                  * ( dir - 3 );

            int const dropsDone = app->inputBuffer.gameEvent.dropCountsSize;

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

            //* Update state
            app->state = STATE_END_TURN;

            return;
        }
    }
}

void handleStateEndTurn( App* const app )
{
    //* End turn, change active player
    app->game.activePlayer
        = ( app->game.activePlayer == PLAYER_WHITE )
              ? PLAYER_BLACK
              : PLAYER_WHITE;

    //* Reset input buffer
    app->inputBuffer = newInputBuffer();
    app->inputBuffer.gameEvent.stonePlayerId = app->game.activePlayer;

    resetCurrentCommand( &app->inputBuffer );

    //* Set first state of new turn
    app->state = STATE_CHOOSE_ACTION;
}

bool handleInputStoneType( App* const app )
{
    if ( !parseInputStoneType( &app->inputBuffer ) )
    {
        return false;
    }

    appendToCurrentCommand(
        &app->inputBuffer,
        STONE_TYPE_CHARS[app->inputBuffer.gameEvent.stoneType]
    );

    return true;
}

bool handleInputFileX( App* const app )
{
    if ( !parseInputFileX( &app->inputBuffer ) )
    {
        return false;
    }

    appendToCurrentCommand(
        &app->inputBuffer,
        FILE_CHARS[app->inputBuffer.gameEvent.fileX]
    );

    return true;
}

bool handleInputRankY( App* const app )
{
    if ( !parseInputRankY( &app->inputBuffer ) )
    {
        return false;
    }

    appendToCurrentCommand(
        &app->inputBuffer,
        RANK_CHARS[app->inputBuffer.gameEvent.rankY]
    );

    return true;
}

bool handleInputDirection( App* const app )
{
    if ( !parseInputDirection( &app->inputBuffer ) )
    {
        return false;
    }

    appendToCurrentCommand(
        &app->inputBuffer,
        DIRECTION_CHARS[app->inputBuffer.gameEvent.direction]
    );

    return true;
}

bool handleInputFirstDropAmount( App* const app )
{
    if ( !parseInputFirstDropAmount( &app->inputBuffer ) )
    {
        return false;
    }

    appendToCurrentCommand(
        &app->inputBuffer,
        app->inputBuffer.gameEvent.dropCounts[app->inputBuffer.gameEvent.dropCountsSize - 1] + '0'
    );

    return true;
}

bool handleInputDropAmount( App* const app )
{
    if ( !parseInputAmount( &app->inputBuffer ) )
    {
        return false;
    }

    appendToCurrentCommand(
        &app->inputBuffer,
        app->inputBuffer.gameEvent.dropCounts[app->inputBuffer.gameEvent.dropCountsSize - 1] + '0'
    );

    return true;
}

