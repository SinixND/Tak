#include "InputParsing.h"

#include "ActionTypeId.h"
#include "CommandId.h"
#include "CommandStateId.h"
#include "FileId.h"
#include "InputBuffer.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <assert.h>

bool parseInput(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize
)
{
    assert(
        pCommand
        && "Pointer is nullptr"
    );

    assert(
        pInputBuffer
        && "Pointer is nullptr"
    );

    switch ( pCommand->state )
    {
        case COMMAND_STATE_NONE:
        case COMMAND_STATE_GET_FIRST_INPUT:
        {
            return parseInputFirst(
                pCommand,
                pInputBuffer,
                boardSize
            );
        }

        case COMMAND_STATE_GET_ACTION_TYPE:
        {
            return parseInputActionType(
                pCommand,
                pInputBuffer
            );
        }

        case COMMAND_STATE_GET_STONE_TYPE:
        {
            return parseInputStoneType(
                pCommand,
                pInputBuffer
            );
        }

        case COMMAND_STATE_GET_FILE_X:
        {
            return parseInputFileX(
                pCommand,
                pInputBuffer
            );
        }

        case COMMAND_STATE_GET_RANK_Y:
        {
            return parseInputRankY(
                pCommand,
                pInputBuffer
            );
        }

        case COMMAND_STATE_GET_DIRECTION:
        {
            return parseInputDirection(
                pCommand,
                pInputBuffer
            );
        }

        case COMMAND_STATE_GET_FIRST_DROP_AMOUNT:
        {
            return parseInputFirstDropAmount(
                pCommand,
                pInputBuffer
            );
        }

        case COMMAND_STATE_GET_DROP_AMOUNT:
        {
            return parseInputDropAmount(
                pCommand,
                pInputBuffer
            );
        }

        default:
            return false;
    }
}

bool parseInputFirst(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize
)
{
    assert(
        pCommand
        && "Pointer is nullptr"
    );

    assert(
        pInputBuffer
        && "Pointer is nullptr"
    );

    switch ( getCommandId(
        pInputBuffer,
        CONTEXT_INPUT_FIRST
    ) )
    {
        case COMMAND_FLAT:
        {
            pCommand->stoneType = STONE_TYPE_FLAT;

            return true;
        }

        case COMMAND_STANDING:
        {
            pCommand->stoneType = STONE_TYPE_STANDING;

            return true;
        }

        case COMMAND_CAPSTONE:
        {
            pCommand->stoneType = STONE_TYPE_CAP;

            return true;
        }

        case COMMAND_CYCLE_STONE_TYPE:
        {
            pCommand->stoneType = ( pCommand->stoneType % 3 ) + 1;

            return true;
        }

        case COMMAND_A:
        {
            pCommand->fileX = FILE_A;

            return true;
        }

        case COMMAND_B:
        {
            pCommand->fileX = FILE_B;

            return true;
        }

        case COMMAND_C:
        {
            pCommand->fileX = FILE_C;

            return true;
        }

        case COMMAND_D:
        {
            pCommand->fileX = FILE_D;

            return true;
        }

        case COMMAND_E:
        {
            pCommand->fileX = FILE_E;

            return true;
        }

        case COMMAND_F:
        {
            pCommand->fileX = FILE_F;

            return true;
        }

        case COMMAND_G:
        {
            pCommand->fileX = FILE_G;

            return true;
        }

        case COMMAND_H:
        {
            pCommand->fileX = FILE_H;

            return true;
        }

        case COMMAND_POSITION:
        {
            /// TODO: Store position in layout
            if (
                ( ( (int)pInputBuffer->position[0] - 21 ) % 4 )
                && ( (int)pInputBuffer->position[1] - 1 ) % 4
            )
            {
                pCommand->fileX
                    = ( (int)pInputBuffer->position[0] - 21 ) / 4;

                pCommand->rankY
                    = ( boardSize - 1 ) - ( ( (int)pInputBuffer->position[1] - 1 ) / 4 );
            }
        }

        case COMMAND_PLACE:
        {
            pCommand->actionType = ACTION_TYPE_PLACE;

            return true;
        }

        case COMMAND_MOVE:
        {
            pCommand->actionType = ACTION_TYPE_LIFT;

            return true;
        }

        default:
            return false;
    }
}

bool parseInputActionType(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    assert(
        pCommand
        && "Pointer is nullptr"
    );

    assert(
        pInputBuffer
        && "Pointer is nullptr"
    );

    switch ( getCommandId(
        pInputBuffer,
        CONTEXT_ACTION_TYPE
    ) )
    {
        case COMMAND_PLACE:
        {
            pCommand->actionType = ACTION_TYPE_PLACE;

            return true;
        }

        case COMMAND_MOVE:
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
    assert(
        pCommand
        && "Pointer is nullptr"
    );

    assert(
        pInputBuffer
        && "Pointer is nullptr"
    );

    switch ( getCommandId(
        pInputBuffer,
        CONTEXT_STONE_TYPE
    ) )
    {
        case COMMAND_FLAT:
        {
            pCommand->stoneType = STONE_TYPE_FLAT;

            return true;
        }

        case COMMAND_STANDING:
        {
            pCommand->stoneType = STONE_TYPE_STANDING;

            return true;
        }

        case COMMAND_CAPSTONE:
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
    assert(
        pCommand
        && "Pointer is nullptr"
    );

    assert(
        pInputBuffer
        && "Pointer is nullptr"
    );

    switch ( getCommandId(
        pInputBuffer,
        CONTEXT_POSITION
    ) )
    {
        case COMMAND_A:
        {
            pCommand->fileX = FILE_A;

            return true;
        }

        case COMMAND_B:
        {
            pCommand->fileX = FILE_B;

            return true;
        }

        case COMMAND_C:
        {
            pCommand->fileX = FILE_C;

            return true;
        }

        case COMMAND_D:
        {
            pCommand->fileX = FILE_D;

            return true;
        }

        case COMMAND_E:
        {
            pCommand->fileX = FILE_E;

            return true;
        }

        case COMMAND_F:
        {
            pCommand->fileX = FILE_F;

            return true;
        }

        case COMMAND_G:
        {
            pCommand->fileX = FILE_G;

            return true;
        }

        case COMMAND_H:
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
    assert(
        pCommand
        && "Pointer is nullptr"
    );

    assert(
        pInputBuffer
        && "Pointer is nullptr"
    );

    switch ( getCommandId(
        pInputBuffer,
        CONTEXT_POSITION
    ) )
    {
        case COMMAND_1:
        {
            pCommand->rankY = RANK_1;

            break;
        }

        case COMMAND_2:
        {
            pCommand->rankY = RANK_2;

            break;
        }

        case COMMAND_3:
        {
            pCommand->rankY = RANK_3;

            break;
        }

        case COMMAND_4:
        {
            pCommand->rankY = RANK_4;

            break;
        }

        case COMMAND_5:
        {
            pCommand->rankY = RANK_5;

            break;
        }

        case COMMAND_6:
        {
            pCommand->rankY = RANK_6;

            break;
        }

        case COMMAND_7:
        {
            pCommand->rankY = RANK_7;

            break;
        }

        case COMMAND_8:
        {
            pCommand->rankY = RANK_8;

            break;
        }

        default:
            return false;
    }

    return true;
}

bool parseInputDirection(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    assert(
        pCommand
        && "Pointer is nullptr"
    );

    assert(
        pInputBuffer
        && "Pointer is nullptr"
    );

    switch ( getCommandId(
        pInputBuffer,
        CONTEXT_DIRECTION
    ) )
    {
        default:
        {
            return false;
        }

        case COMMAND_UP:
        {
            pCommand->direction = DIR_UP;

            return true;
        }

        case COMMAND_DOWN:
        {
            pCommand->direction = DIR_DOWN;

            return true;
        }

        case COMMAND_LEFT:
        {
            pCommand->direction = DIR_LEFT;

            return true;
        }

        case COMMAND_RIGHT:
        {
            pCommand->direction = DIR_RIGHT;

            return true;
        }
    }
}

bool parseInputFirstDropAmount(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    assert(
        pCommand
        && "Pointer is nullptr"
    );

    assert(
        pInputBuffer
        && "Pointer is nullptr"
    );

    assert(
        !pCommand->drops
        && "Drops value invalid"
    );

    switch ( getCommandId(
        pInputBuffer,
        CONTEXT_AMOUNT
    ) )
    {
        case COMMAND_0:
        {
            pCommand->dropCounts[0] = 0;

            break;
        }

        case COMMAND_1:
        {
            pCommand->dropCounts[0] = 1;

            break;
        }

        case COMMAND_2:
        {
            pCommand->dropCounts[0] = 2;

            break;
        }

        case COMMAND_3:
        {
            pCommand->dropCounts[0] = 3;

            break;
        }

        case COMMAND_4:
        {
            pCommand->dropCounts[0] = 4;

            break;
        }

        case COMMAND_5:
        {
            pCommand->dropCounts[0] = 5;

            break;
        }

        case COMMAND_6:
        {
            pCommand->dropCounts[0] = 6;

            break;
        }

        case COMMAND_7:
        {
            pCommand->dropCounts[0] = 7;

            break;
        }

        case COMMAND_8:
        {
            pCommand->dropCounts[0] = 8;

            break;
        }

        default:
            return false;
    }

    return true;
}

bool parseInputDropAmount(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
)
{
    assert(
        pCommand
        && "Pointer is nullptr"
    );

    assert(
        pInputBuffer
        && "Pointer is nullptr"
    );

    assert(
        pCommand->drops > 0
        && "Drops value invalid"
    );

    switch ( getCommandId(
        pInputBuffer,
        CONTEXT_AMOUNT
    ) )
    {
        case COMMAND_1:
        {
            pCommand->dropCounts[pCommand->drops] = 1;

            break;
        }

        case COMMAND_2:
        {
            pCommand->dropCounts[pCommand->drops] = 2;

            break;
        }

        case COMMAND_3:
        {
            pCommand->dropCounts[pCommand->drops] = 3;

            break;
        }

        case COMMAND_4:
        {
            pCommand->dropCounts[pCommand->drops] = 4;

            break;
        }

        case COMMAND_5:
        {
            pCommand->dropCounts[pCommand->drops] = 5;

            break;
        }

        case COMMAND_6:
        {
            pCommand->dropCounts[pCommand->drops] = 6;

            break;
        }

        case COMMAND_7:
        {
            pCommand->dropCounts[pCommand->drops] = 7;

            break;
        }

        case COMMAND_8:
        case COMMAND_ALL:
        {
            pCommand->dropCounts[pCommand->drops] = 8;

            break;
        }

        default:
            return false;
    }

    return true;
}

