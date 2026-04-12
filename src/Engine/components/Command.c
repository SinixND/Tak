#include "Command.h"

#include "ActionTypeId.h"
#include "CommandStateId.h"
#include "DirectionId.h"
#include "FileId.h"
#include "GameConstants.h"
#include "InputBuffer.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

Command newCommand( void )
{
    Command command = {
        .playerId = PLAYER_NONE,
        .actionType = ACTION_TYPE_NONE,
        .stoneType = STONE_TYPE_NONE,
        .fileX = FILE_NONE,
        .rankY = RANK_NONE,
        .direction = DIR_NONE,
        .drops = -1,
    };

    for ( int i = 0; i < BOARD_SIZE_MAX; ++i )
    {
        command.dropCounts[i] = -1;
    }

    return command;
}

bool isCommandComplete( Command const* const pCommand )
{
    assert(
        pCommand
        && "Pointer is nullptr"
    );

    switch ( pCommand->actionType )
    {
        default:
        case ACTION_TYPE_NONE:
            return false;

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
                && ( pCommand->dropCounts[pCommand->drops] > 0 )
            );
        }
    }
}

void runBuildCommandFSM(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    switch ( pCommand->state )
    {
        default:
            return;

        case STATE_GET_ACTION:
        {
            handleStateGetAction(
                pCommand,
                pInputBuffer
            );

            return;
        }
    }
}

void handleStateGetAction(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    if ( !parseInputAction(
             pCommand,
             pInputBuffer
         ) )
    {
        return;
    }

    //* Change state
    switch ( pCommand->actionType )
    {
        default:
            return;

        case ACTION_TYPE_PLACE:
        {
            pCommand->state = STATE_GET_STONE_TYPE;

            return;
        }

        case ACTION_TYPE_LIFT:
        {
            pCommand->state = STATE_GET_FILE_X;

            return;
        }
    }
}

bool parseInputAction(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    switch ( pInputBuffer->keyboard )
    {
        default:
        {
            return false;
        }

        case INPUT_P:
        {
            pCommand->actionType = ACTION_TYPE_PLACE;

            return true;
        }

        case INPUT_M:
        {
            pCommand->actionType = ACTION_TYPE_LIFT;

            return true;
        }
    }
}
