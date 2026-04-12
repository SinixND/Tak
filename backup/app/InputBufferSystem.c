#include "InputBufferSystem.h"

#include "GameEventSystem.h"
#include "InputBuffer.h"
#include "Layout.h"
#include <assert.h>
#include <stdbool.h>

InputBuffer newInputBuffer( void )
{
    return (InputBuffer){
        .gameEvent = newGameEvent(),
        .lastInput = INPUT_NONE,
        .currentCommand = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        .currentCommandSize = 0,
    };
}

void appendToCurrentCommand(
    InputBuffer* const inputBuffer,
    char const ch
)
{
    inputBuffer->currentCommand[inputBuffer->currentCommandSize] = ch;

    ++inputBuffer->currentCommandSize;
}

void resetCurrentCommand( InputBuffer* const inputBuffer )
{
    for ( int idx = 0; idx < MAX_COMMAND_LENGTH; ++idx )
    {
        inputBuffer->currentCommand[idx] = ' ';
    }

    //* Null terminate command
    inputBuffer->currentCommand[MAX_COMMAND_LENGTH - 1] = 0;

    inputBuffer->currentCommandSize = 0;
}

bool parseInputAction( InputBuffer* const inputBuffer )
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

        //* TODO: Check if necessary
        // case INPUT_L:
        // {
        //     pCommand->actionType = ACTION_TYPE_LIFT;
        //
        //     return true;
        // }
        //
        // case INPUT_D:
        // {
        //     pCommand->actionType = ACTION_TYPE_DROP;
        //
        //     return true;
        // }
        //
        case INPUT_M:
        {
            pCommand->actionType = ACTION_TYPE_LIFT;

            return true;
        }
    }
}

bool parseInputFileX( InputBuffer* const inputBuffer )
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

bool parseInputRankY( InputBuffer* const inputBuffer )
{
    switch ( pInputBuffer->keyboard )
    {
        default:
        {
            return false;
        }

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
    }
}

bool parseInputStoneType( InputBuffer* const inputBuffer )
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

bool parseInputDirection( InputBuffer* const inputBuffer )
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

bool parseInputFirstDropAmount( InputBuffer* const inputBuffer )
{
    assert(
        pCommand->dropCountsSize >= 0
        && pCommand->dropCountsSize < BOARD_WIDTH_MAX
        && "Invalid dropsDone value"
    );

    int dropCount = 0;

    switch ( pInputBuffer->keyboard )
    {
        default:
            return false;

        case INPUT_0:
        {
            dropCount = 0;

            break;
        }

        case INPUT_1:
        {
            dropCount = 1;

            break;
        }

        case INPUT_2:
        {
            dropCount = 2;

            break;
        }

        case INPUT_3:
        {
            dropCount = 3;

            break;
        }

        case INPUT_4:
        {
            dropCount = 4;

            break;
        }

        case INPUT_5:
        {
            dropCount = 5;

            break;
        }

        case INPUT_6:
        {
            dropCount = 6;

            break;
        }

        case INPUT_7:
        {
            dropCount = 7;

            break;
        }

        case INPUT_8:
        {
            dropCount = 8;

            break;
        }
    }

    if ( ( pCommand->droppedCount + dropCount ) > pCommand->liftCount )
    {
        return false;
    }

    pCommand->dropCounts[pCommand->dropCountsSize] = dropCount;
    pCommand->droppedCount += dropCount;
    ++pCommand->dropCountsSize;

    return true;
}

bool parseInputAmount( InputBuffer* const inputBuffer )
{
    assert(
        pCommand->dropCountsSize >= 0
        && pCommand->dropCountsSize < BOARD_WIDTH_MAX
        && "Invalid dropsDone value"
    );

    int dropCount = 0;

    switch ( pInputBuffer->keyboard )
    {
        default:
            return false;

        case INPUT_1:
        {
            dropCount = 1;

            break;
        }

        case INPUT_2:
        {
            dropCount = 2;

            break;
        }

        case INPUT_3:
        {
            dropCount = 3;

            break;
        }

        case INPUT_4:
        {
            dropCount = 4;

            break;
        }

        case INPUT_5:
        {
            dropCount = 5;

            break;
        }

        case INPUT_6:
        {
            dropCount = 6;

            break;
        }

        case INPUT_7:
        {
            dropCount = 7;

            break;
        }

        case INPUT_8:
        {
            dropCount = 8;

            break;
        }
    }

    if ( ( pCommand->droppedCount + dropCount ) > pCommand->liftCount )
    {
        return false;
    }

    pCommand->dropCounts[pCommand->dropCountsSize] += dropCount;
    pCommand->droppedCount += dropCount;
    ++pCommand->dropCountsSize;

    return true;
}

