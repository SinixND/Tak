#include "Command.h"

#include "ActionTypeId.h"
#include "CommandStateId.h"
#include "DirectionId.h"
#include "FileId.h"
#include "Game.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

Command newCommand( PlayerId const playerId )
{
    Command command = {
        .state = STATE_GET_ACTION_TYPE,
        .playerId = playerId,
        .actionType = ACTION_TYPE_NONE,
        .stoneType = STONE_TYPE_NONE,
        .fileX = FILE_NONE,
        .rankY = RANK_NONE,
        .direction = DIR_NONE,
        .drops = 0,
    };

    for ( int i = 0; i < BOARD_SIZE_MAX; ++i )
    {
        command.dropCounts[i] = -1;
    }

    return command;
}

void setNextCommandState(
    Command* const pCommand,
    Game const* const pGame
)
{
    switch ( pCommand->state )
    {
        case STATE_NONE:
        {
            assert( !"Invalid command state" );
            return;
        }

        case STATE_GET_ACTION_TYPE:
        {
            pCommand->state
                = ( pCommand->actionType == ACTION_TYPE_PLACE )
                      ? STATE_GET_STONE_TYPE
                      : STATE_GET_FILE_X;

            return;
        }

        case STATE_GET_STONE_TYPE:
        {
            pCommand->state = STATE_GET_FILE_X;

            return;
        }

        case STATE_GET_FILE_X:
        {
            pCommand->state = STATE_GET_RANK_Y;

            return;
        }

        case STATE_GET_RANK_Y:
        {
            assert(
                pCommand->actionType != ACTION_TYPE_NONE
                && "Invalid action type"
            );

            pCommand->state
                = ( pCommand->actionType == ACTION_TYPE_PLACE )
                      ? STATE_GET_ACTION_TYPE
                      : STATE_GET_DIRECTION;

            return;
        }

        case STATE_GET_DIRECTION:
        {
            pCommand->state = STATE_GET_FIRST_DROP_AMOUNT;

            return;
        }

        case STATE_GET_FIRST_DROP_AMOUNT:
        case STATE_GET_DROP_AMOUNT:
        {
            pCommand->state
                = ( pCommand->dropCounts[pCommand->drops] >= pGame->stackBuffer.stoneCount )
                      ? STATE_GET_ACTION_TYPE
                      : STATE_GET_DROP_AMOUNT;

            return;
        }

        default:
            return;
    }
}

bool isCommandReady( Command const* const pCommand )
{
    assert(
        pCommand
        && "Pointer is nullptr"
    );

    switch ( pCommand->actionType )
    {
        case ACTION_TYPE_PLACE:
        {
            return (
                ( pCommand->playerId != PLAYER_NONE )
                && ( pCommand->fileX != FILE_NONE )
                && ( pCommand->rankY != RANK_NONE )
                && ( pCommand->stoneType != STONE_TYPE_NONE )
            );
        }

        case ACTION_TYPE_LIFT:
        {
            return (
                ( pCommand->fileX != FILE_NONE )
                && ( pCommand->rankY != RANK_NONE )
            );
        }

        case ACTION_TYPE_DROP:
        {
            return (
                ( pCommand->fileX != FILE_NONE )
                && ( pCommand->rankY != RANK_NONE )
                && ( pCommand->direction != DIR_NONE )
                && ( ( !pCommand->drops )
                         ? pCommand->dropCounts[pCommand->drops] >= 0
                         : pCommand->dropCounts[pCommand->drops] > 0 )
            );
        }

        default:
            return false;
    }
}

void updateCommandPostEvent( Command* const pCommand )
{
    /// Un-ready command by updating drop count
    if ( pCommand->actionType == ACTION_TYPE_DROP )
    {
        ++pCommand->drops;

        return;
    }

    /// Advance from lift to drop action
    if ( pCommand->actionType == ACTION_TYPE_LIFT )
    {
        pCommand->actionType = ACTION_TYPE_DROP;
    }
}

void prepareCommand( Command* const pCommand )
{
    assert(
        pCommand->playerId != PLAYER_NONE
        && "Invalid playerId"
    );

    if ( pCommand->playerId == PLAYER_WHITE )
    {
        *pCommand = newCommand( PLAYER_BLACK );
    }
    else
    {
        *pCommand = newCommand( PLAYER_WHITE );
    }
}
