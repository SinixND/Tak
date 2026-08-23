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
        .state = COMMAND_STATE_DEFAULT,
        .playerId = playerId,
        .actionType = ACTION_TYPE_NONE,
        .stoneType = STONE_TYPE_NONE,
        .fileX = FILE_NONE,
        .rankY = RANK_NONE,
        .direction = DIR_NONE,
        .drops = 0,
        .bufferedDropCount = 0,
    };

    for ( int n = 0; n < BOARD_SIZE_MAX; ++n )
    {
        command.dropCounts[n] = -1;
    }

    return command;
}

void setNextCommandState(
    Command* const pCommand,
    Game const* const pGame
)
{
    assert(
        pCommand
        && "Pointer is nullptr"
    );

    assert(
        pGame
        && "Pointer is nullptr"
    );

    switch ( pCommand->state )
    {
        case COMMAND_STATE_NONE:
        case COMMAND_STATE_DEFAULT:
        {
            /// First: Action
            if ( pCommand->actionType == ACTION_TYPE_PLACE
                 && pCommand->stoneType == STONE_TYPE_NONE )
            {
                pCommand->state
                    = COMMAND_STATE_GET_STONE_TYPE;

                return;
            }

            if ( pCommand->actionType == ACTION_TYPE_LIFT )
            {
                pCommand->state
                    = COMMAND_STATE_GET_POSITION;

                return;
            }

            /// First: FileX & RankY
            if ( pCommand->fileX != FILE_NONE
                 && pCommand->rankY != RANK_NONE )
            {
                pCommand->state
                    = COMMAND_STATE_DEFAULT;

                return;
            }

            /// First: FileX
            if ( pCommand->fileX != FILE_NONE )
            {
                pCommand->state
                    = COMMAND_STATE_GET_RANK_Y;

                return;
            }

            return;
        }

        case COMMAND_STATE_GET_ACTION_TYPE:
        {
            pCommand->state
                = ( pCommand->actionType == ACTION_TYPE_PLACE
                    && pCommand->stoneType == STONE_TYPE_NONE )
                      ? COMMAND_STATE_GET_STONE_TYPE
                      : COMMAND_STATE_GET_POSITION;

            return;
        }

        case COMMAND_STATE_GET_STONE_TYPE:
        {
            pCommand->state = COMMAND_STATE_GET_POSITION;

            return;
        }

        case COMMAND_STATE_GET_POSITION:
        {
            pCommand->state = COMMAND_STATE_GET_RANK_Y;

            return;
        }

        case COMMAND_STATE_GET_RANK_Y:
        {
            pCommand->state
                = ( pCommand->actionType == ACTION_TYPE_LIFT )
                      ? COMMAND_STATE_GET_DIRECTION
                      : COMMAND_STATE_DEFAULT;

            return;
        }

        case COMMAND_STATE_GET_DIRECTION:
        {
            pCommand->state = COMMAND_STATE_GET_FIRST_DROP_AMOUNT;

            return;
        }

        case COMMAND_STATE_GET_FIRST_DROP_AMOUNT:
        case COMMAND_STATE_GET_DROP_AMOUNT:
        {
            pCommand->state
                = ( pCommand->dropCounts[pCommand->drops] >= pGame->stackBuffer.stoneCount )
                      ? COMMAND_STATE_DEFAULT
                      : COMMAND_STATE_GET_DROP_AMOUNT;

            return;
        }

        default:
            return;
    }
}

bool isCommandCompleteForEvent( Command const* const pCommand )
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
    assert(
        pCommand
        && "Pointer is nullptr"
    );

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

