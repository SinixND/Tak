#include "AppSystem.h"

#include "ActionTypeId.h"
#include "App.h"
#include "AppState.h"
#include "DirectionId.h"
#include "FileId.h"
#include "GameSystem.h"
#include "InputBufferSystem.h"
#include "PlayerId.h"
#include "Prompt.h"
#include "Prompts.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

/// Choose backend
#ifdef BACKEND_NCURSES
#include "ContextSystem.h"
#endif

App newApp( int const boardSize )
{
    assert(
        ( boardSize >= BOARD_WIDTH_MIN )
        && "Board width value too small"
    );

    assert(
        ( boardSize <= BOARD_WIDTH_MAX )
        && "Board width value too big"
    );

    App app = {
        .game = newGame( boardSize ),
        .inputBuffer = newInputBuffer(),
        .state = STATE_FIRST_TURN,
        .prompt = PROMPTS[STATE_FIRST_TURN],
        .shouldClose = false,
    };

    // TODO: check if needed
    // app.inputBuffer.gameEvent.stoneId = PLAYER_BLACK;
    // app.inputBuffer.gameEvent.actionType = ACTION_TYPE_PLACE;
    // app.inputBuffer.gameEvent.stoneType = STONE_TYPE_FLAT;

    return app;
}

void setupApp( void )
{
    setupBackend();
}

void closeApp( void )
{
    closeBackend();
}

void updateApp( App* const app )
{
    handleGlobalInput( app );
    updateState( app );
}

void handleGlobalInput( App* const app )
{
    /// Conditionally terminate by
    /// changing main while loop condition
    // NOTE: Maybe extract into separate function later
    app->shouldClose
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

        case STATE_GET_STONE_TYPE:
        {
            handleStateGetStoneType( app );

            return;
        }

        case STATE_GET_FILE_X:
        {
            handleStateGetFileX( app );

            return;
        }

        case STATE_GET_RANK_Y:
        {
            handleStateGetRankY( app );

            return;
        }

        case STATE_GET_DIRECTION:
        {
            handleStateGetDirection( app );

            return;
        }

        case STATE_GET_FIRST_DROP_AMOUNT:
        {
            handleStateGetFirstDropAmount( app );

            return;
        }

        case STATE_GET_DROP_AMOUNT:
        {
            handleStateGetDropAmount( app );

            return;
        }

        case STATE_RESOLVE_ACTION:
        {
            handleStateResolveAction( app );

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
    /// Update prompt
    app->prompt = PROMPTS[state];
}

void handleStateFirstTurn( App* const app )
{
    /// Call state functions explicitly for this one time only state
    if ( app->inputBuffer.gameEvent.fileX < FILE_A )
    {
        app->prompt.input = "File / Col";
        app->prompt.options = "A - H     ";

        handleStateGetFileX( app );

        // Keep state
        app->state = STATE_FIRST_TURN;

        return;
    }

    if ( app->inputBuffer.gameEvent.rankY < RANK_1 )
    {
        handleStateGetRankY( app );

        // Keep state
        app->state = STATE_FIRST_TURN;

        return;
    }

    /// Prepare game event for first turn
    app->inputBuffer.gameEvent.actionType = ACTION_TYPE_PLACE;
    app->inputBuffer.gameEvent.stoneId = PLAYER_BLACK;
    app->inputBuffer.gameEvent.stoneType = STONE_TYPE_FLAT;

    handleStateResolveAction( app );
    handleStateEndTurn( app );

    changeState(
        app,
        STATE_SECOND_TURN
    );

    return;
}

void handleStateSecondTurn( App* const app )
{
    /// Call state functions explicitly for this one time only state
    if ( app->inputBuffer.gameEvent.fileX < FILE_A )
    {
        handleStateGetFileX( app );

        // Keep state
        app->state = STATE_SECOND_TURN;

        return;
    }

    if ( app->inputBuffer.gameEvent.rankY < RANK_1 )
    {
        handleStateGetRankY( app );

        // Keep state
        app->state = STATE_SECOND_TURN;

        return;
    }

    /// Prepare game event for first turn
    app->inputBuffer.gameEvent.actionType = ACTION_TYPE_PLACE;
    app->inputBuffer.gameEvent.stoneId = PLAYER_WHITE;
    app->inputBuffer.gameEvent.stoneType = STONE_TYPE_FLAT;

    /// Enter general game loop
    changeState(
        app,
        STATE_RESOLVE_ACTION
    );

    return;
}

void handleStateChooseAction( App* const app )
{
    if ( !parseInputActionType( &app->inputBuffer ) )
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

    /// Change state
    switch ( app->inputBuffer.gameEvent.actionType )
    {
        default:
            return;

        case ACTION_TYPE_PLACE:
        {
            changeState(
                app,
                STATE_GET_STONE_TYPE
            );

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            changeState(
                app,
                STATE_GET_FILE_X
            );

            return;
        }
    }
}

void handleStateGetStoneType( App* const app )
{
    if ( !parseInputStoneType( &app->inputBuffer ) )
    {
        return;
    }

    appendToCurrentCommand(
        &app->inputBuffer,
        STONE_TYPE_CHARS[app->inputBuffer.gameEvent.stoneType]
    );

    changeState(
        app,
        STATE_GET_FILE_X
    );

    return;
}

void handleStateGetFileX( App* const app )
{
    if ( !parseInputFileX( &app->inputBuffer ) )
    {
        return;
    }

    appendToCurrentCommand(
        &app->inputBuffer,
        FILE_CHARS[app->inputBuffer.gameEvent.fileX]
    );

    changeState(
        app,
        STATE_GET_RANK_Y
    );

    return;
}

void handleStateGetRankY( App* const app )
{
    if ( !parseInputRankY( &app->inputBuffer ) )
    {
        return;
    }

    appendToCurrentCommand(
        &app->inputBuffer,
        RANK_CHARS[app->inputBuffer.gameEvent.rankY]
    );

    switch ( app->inputBuffer.gameEvent.actionType )
    {
        default:
            return;

        case ACTION_TYPE_PLACE:
        {
            changeState(
                app,
                STATE_RESOLVE_ACTION
            );

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            changeState(
                app,
                STATE_GET_DIRECTION
            );

            return;
        }
    }

    return;
}

void handleStateGetDirection( App* const app )
{
    if ( !parseInputDirection( &app->inputBuffer ) )
    {
        return;
    }

    appendToCurrentCommand(
        &app->inputBuffer,
        DIRECTION_CHARS[app->inputBuffer.gameEvent.direction]
    );

    changeState(
        app,
        STATE_GET_FIRST_DROP_AMOUNT
    );

    return;
}

void handleStateGetFirstDropAmount( App* const app )
{
    if ( !parseInputFirstDropAmount( &app->inputBuffer ) )
    {
        return;
    }

    appendToCurrentCommand(
        &app->inputBuffer,
        app->inputBuffer.gameEvent.dropCounts[app->inputBuffer.gameEvent.dropCountsSize - 1] + '0'
    );

    changeState(
        app,
        STATE_RESOLVE_ACTION
    );

    return;
}

void handleStateGetDropAmount( App* const app )
{
    if ( !parseInputAmount( &app->inputBuffer ) )
    {
        return;
    }

    appendToCurrentCommand(
        &app->inputBuffer,
        app->inputBuffer.gameEvent.dropCounts[app->inputBuffer.gameEvent.dropCountsSize - 1] + '0'
    );

    changeState(
        app,
        STATE_RESOLVE_ACTION
    );

    return;
}

void handleStateResolveAction( App* const app )
{
    // TODO: Implement rules

    /// Update game
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
                app->inputBuffer.gameEvent.stoneId,
                app->inputBuffer.gameEvent.fileX,
                app->inputBuffer.gameEvent.rankY,
                app->inputBuffer.gameEvent.stoneType
            );

            changeState(
                app,
                STATE_END_TURN
            );

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            liftStack(
                &app->game,
                app->inputBuffer.gameEvent.fileX,
                app->inputBuffer.gameEvent.rankY
            );

            app->inputBuffer.gameEvent.liftCount = app->game.stackBuffer.stoneCount;
            app->inputBuffer.gameEvent.actionType = ACTION_TYPE_DROP;

            changeState(
                app,
                STATE_GET_FIRST_DROP_AMOUNT
            );

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

            changeState(
                app,
                ( app->inputBuffer.gameEvent.liftCount
                  > app->inputBuffer.gameEvent.droppedCount )
                    ? STATE_GET_DROP_AMOUNT
                    : STATE_END_TURN
            );

            return;
        }
    }
}

void handleStateEndTurn( App* const app )
{
    /// End turn, change active player
    app->game.activePlayer
        = ( app->game.activePlayer == PLAYER_WHITE )
              ? PLAYER_BLACK
              : PLAYER_WHITE;

    /// Reset input buffer
    app->inputBuffer = newInputBuffer();
    app->inputBuffer.gameEvent.stoneId = app->game.activePlayer;

    resetCurrentCommand( &app->inputBuffer );

    /// Start new turn
    changeState(
        app,
        STATE_CHOOSE_ACTION
    );
}

