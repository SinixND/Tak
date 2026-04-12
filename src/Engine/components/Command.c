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
            handleStateGetFileX(
                pCommand,
                pInputBuffer
            );

            return;
        }

        case STATE_GET_RANK_Y:
        {
            handleStateGetRankY(
                pCommand,
                pInputBuffer
            );

            return;
        }

        default:
            return;
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

    CommandStateId const nextState
        = ( pCommand->actionType == ACTION_TYPE_PLACE )
              ? STATE_GET_STONE_TYPE
              //* == ACTION_TYPE_LIFT
              : STATE_GET_FILE_X;

    //* Change state
    pCommand->state = nextState;

    return;
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
    pCommand->state = STATE_GET_FILE_X;

    return;
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
    pCommand->state = STATE_GET_RANK_Y;

    return;
}

void handleStateGetRankY(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    if ( !parseInputRankY(
             pCommand,
             pInputBuffer
         ) )
    {
        return;
    }

    CommandStateId const nextState
        = ( pCommand->actionType == ACTION_TYPE_PLACE )
              ? STATE_GET_ACTION
              //* == ACTION_TYPE_LIFT
              : STATE_GET_DIRECTION;

    ActionType const nextActionType
        = ( pCommand->actionType == ACTION_TYPE_PLACE )
              ? ACTION_TYPE_NONE
              //* == ACTION_TYPE_LIFT
              : ACTION_TYPE_DROP;

    //* Change state
    pCommand->state = nextState;
    //* Update command action type
    pCommand->actionType = nextActionType;

    return;
}

void handleStateGetDirection(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    if ( !parseInputDirection(
             pCommand,
             pInputBuffer
         ) )
    {
        return;
    }

    //* Change state
    pCommand->state = STATE_GET_FIRST_DROP_AMOUNT;

    return;
}

bool parseInputAction(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    switch ( pInputBuffer->keyboard )
    {
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

        default:
            return false;
    }
}

bool parseInputStoneType(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    switch ( pInputBuffer->keyboard )
    {
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

        default:
            return false;
    }
}

bool parseInputFileX(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    switch ( pInputBuffer->keyboard )
    {
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

        default:
            return false;
    }
}

bool parseInputRankY(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    switch ( pInputBuffer->keyboard )
    {
        case INPUT_1:
        {
            pCommand->rankY = RANK_1;

            return true;
        }

        case INPUT_2:
        {
            pCommand->rankY = RANK_2;

            return true;
        }

        case INPUT_3:
        {
            pCommand->rankY = RANK_3;

            return true;
        }

        case INPUT_4:
        {
            pCommand->rankY = RANK_4;

            return true;
        }

        case INPUT_5:
        {
            pCommand->rankY = RANK_5;

            return true;
        }

        case INPUT_6:
        {
            pCommand->rankY = RANK_6;

            return true;
        }

        case INPUT_7:
        {
            pCommand->rankY = RANK_7;

            return true;
        }

        case INPUT_8:
        {
            pCommand->rankY = RANK_8;

            return true;
        }

        default:
            return false;
    }
}

bool parseInputDirection( Command* const pCommand, InputBuffer const* const pInputBuffer )
{
    switch ( pInputBuffer->keyboard )
    {
        default:
        {
            return false;
        }

        case INPUT_N:
        {
            pCommand->direction = DIR_UP;

            return true;
        }

        case INPUT_E:
        {
            pCommand->direction = DIR_RIGHT;

            return true;
        }

        case INPUT_S:
        {
            pCommand->direction = DIR_DOWN;

            return true;
        }

        case INPUT_W:
        {
            pCommand->direction = DIR_LEFT;

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

        default:
            return false;
    }
}
