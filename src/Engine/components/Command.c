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
        .state = STATE_GET_ACTION,
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

        case STATE_GET_STONE_TYPE:
        {
            handleStateGetStoneType(
                pCommand,
                pInputBuffer
            );

            return;
        }

        case STATE_GET_FILE_X:
        {
            // handleStateGetFileX(
            //     pCommand,
            //     pInputBuffer
            // );

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

void handleStateGetStoneType(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    if ( !parseInputStoneType(
             pCommand,
             pInputBuffer
         ) )
    {
        return;
    }

    //* Change state
    switch ( pCommand->stoneType )
    {
        default:
            return;

        case STONE_TYPE_FLAT:
        case STONE_TYPE_STANDING:
        case STONE_TYPE_CAP:
        {
            pCommand->state = STATE_GET_FILE_X;

            return;
        }
    }
}

void handleStateGetFileX(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    if ( !parseInputFileX(
             pCommand,
             pInputBuffer
         ) )
    {
        return;
    }

    //* Change state
    switch ( pCommand->fileX )
    {
        default:
            return;

        case FILE_A:
        case FILE_B:
        case FILE_C:
        case FILE_D:
        case FILE_E:
        case FILE_F:
        case FILE_G:
        case FILE_H:
        {
            pCommand->state = STATE_GET_RANK_Y;

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

bool parseInputStoneType(
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

        case INPUT_F:
        {
            pCommand->stoneType = STONE_TYPE_FLAT;

            return true;
        }

        case INPUT_S:
        {
            pCommand->stoneType = STONE_TYPE_STANDING;

            return true;
        }

        case INPUT_C:
        {
            pCommand->stoneType = STONE_TYPE_CAP;

            return true;
        }
    }
}

bool parseInputFileX(
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

        case INPUT_A:
        {
            pCommand->fileX = FILE_A;

            return true;
        }

        case INPUT_B:
        {
            pCommand->fileX = FILE_B;

            return true;
        }

        case INPUT_C:
        {
            pCommand->fileX = FILE_C;

            return true;
        }

        case INPUT_D:
        {
            pCommand->fileX = FILE_D;

            return true;
        }

        case INPUT_E:
        {
            pCommand->fileX = FILE_E;

            return true;
        }

        case INPUT_F:
        {
            pCommand->fileX = FILE_F;

            return true;
        }

        case INPUT_G:
        {
            pCommand->fileX = FILE_G;

            return true;
        }

        case INPUT_H:
        {
            pCommand->fileX = FILE_H;

            return true;
        }
    }
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
