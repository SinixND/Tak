#include "InputBufferSystem.h"

#include "GameEventSystem.h"
#include "InputBuffer.h"
#include <assert.h>
#include <stdbool.h>

InputBuffer newInputBuffer( void )
{
    return (InputBuffer){
        .gameEvent = newGameEvent(),
        .lastInput = INPUT_NONE,
        .currentInput = { 0 },
        .inputLength = 0,
    };
}

bool parseInputForAction( InputBuffer* const inputBuffer )
{
    switch ( inputBuffer->lastInput )
    {
        default:
        {
            return false;
        }

        case INPUT_P:
        {
            inputBuffer->gameEvent.actionType = ACTION_TYPE_PLACE;

            return true;
        }

        case INPUT_L:
        {
            inputBuffer->gameEvent.actionType = ACTION_TYPE_LIFT;

            return true;
        }

        case INPUT_D:
        {
            inputBuffer->gameEvent.actionType = ACTION_TYPE_DROP;

            return true;
        }
    }
}

bool parseInputForFileX( InputBuffer* const inputBuffer )
{
    switch ( inputBuffer->lastInput )
    {
        default:
        {
            return false;
        }

        case INPUT_A:
        {
            inputBuffer->gameEvent.fileX = FILE_A;

            return true;
        }

        case INPUT_B:
        {
            inputBuffer->gameEvent.fileX = FILE_B;

            return true;
        }

        case INPUT_C:
        {
            inputBuffer->gameEvent.fileX = FILE_C;

            return true;
        }

        case INPUT_D:
        {
            inputBuffer->gameEvent.fileX = FILE_D;

            return true;
        }

        case INPUT_E:
        {
            inputBuffer->gameEvent.fileX = FILE_E;

            return true;
        }

        case INPUT_F:
        {
            inputBuffer->gameEvent.fileX = FILE_F;

            return true;
        }

        case INPUT_G:
        {
            inputBuffer->gameEvent.fileX = FILE_G;

            return true;
        }

        case INPUT_H:
        {
            inputBuffer->gameEvent.fileX = FILE_H;

            return true;
        }
    }
}

bool parseInputForRankY( InputBuffer* const inputBuffer )
{
    switch ( inputBuffer->lastInput )
    {
        default:
        {
            return false;
        }

        case INPUT_1:
        {
            inputBuffer->gameEvent.rankY = RANK_1;

            return true;
        }

        case INPUT_2:
        {
            inputBuffer->gameEvent.rankY = RANK_2;

            return true;
        }

        case INPUT_3:
        {
            inputBuffer->gameEvent.rankY = RANK_3;

            return true;
        }

        case INPUT_4:
        {
            inputBuffer->gameEvent.rankY = RANK_4;

            return true;
        }

        case INPUT_5:
        {
            inputBuffer->gameEvent.rankY = RANK_5;

            return true;
        }

        case INPUT_6:
        {
            inputBuffer->gameEvent.rankY = RANK_6;

            return true;
        }

        case INPUT_7:
        {
            inputBuffer->gameEvent.rankY = RANK_7;

            return true;
        }

        case INPUT_8:
        {
            inputBuffer->gameEvent.rankY = RANK_8;

            return true;
        }
    }
}

bool parseInputForStoneType( InputBuffer* const inputBuffer )
{
    switch ( inputBuffer->lastInput )
    {
        default:
        {
            return false;
        }

        case INPUT_F:
        {
            inputBuffer->gameEvent.stoneType = STONE_TYPE_FLAT;

            return true;
        }

        case INPUT_S:
        {
            inputBuffer->gameEvent.stoneType = STONE_TYPE_STANDING;

            return true;
        }

        case INPUT_C:
        {
            inputBuffer->gameEvent.stoneType = STONE_TYPE_CAP;

            return true;
        }
    }
}

bool parseInputForDirection( InputBuffer* const inputBuffer )
{
    switch ( inputBuffer->lastInput )
    {
        default:
        {
            return false;
        }

        case INPUT_N:
        {
            inputBuffer->gameEvent.direction = DIR_UP;

            return true;
        }

        case INPUT_E:
        {
            inputBuffer->gameEvent.direction = DIR_RIGHT;

            return true;
        }

        case INPUT_S:
        {
            inputBuffer->gameEvent.direction = DIR_DOWN;

            return true;
        }

        case INPUT_W:
        {
            inputBuffer->gameEvent.direction = DIR_LEFT;

            return true;
        }
    }
}

bool parseInputForFirstDropAmount( InputBuffer* const inputBuffer )
{
    assert(
        inputBuffer->gameEvent.dropsDone >= 0
        && inputBuffer->gameEvent.dropsDone < BOARD_WIDTH_MAX
        && "Invalid dropsDone value"
    );

    int dropCount = 0;

    switch ( inputBuffer->lastInput )
    {
        default:
        {
            //* Do nothing
            return false;
        }

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

    if ( ( inputBuffer->gameEvent.droppedCount + dropCount ) > inputBuffer->gameEvent.liftCount )
    {
        return false;
    }

    inputBuffer->gameEvent.dropCounts[inputBuffer->gameEvent.dropsDone] = dropCount;
    inputBuffer->gameEvent.droppedCount += dropCount;
    ++inputBuffer->gameEvent.dropsDone;

    return true;
}

bool parseInputForAmount( InputBuffer* const inputBuffer )
{
    assert(
        inputBuffer->gameEvent.dropsDone >= 0
        && inputBuffer->gameEvent.dropsDone < BOARD_WIDTH_MAX
        && "Invalid dropsDone value"
    );

    int dropCount = 0;

    switch ( inputBuffer->lastInput )
    {
        default:
        {
            //* Do nothing
            return false;
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

    if ( ( inputBuffer->gameEvent.droppedCount + dropCount ) > inputBuffer->gameEvent.liftCount )
    {
        return false;
    }

    inputBuffer->gameEvent.dropCounts[inputBuffer->gameEvent.dropsDone] += dropCount;
    inputBuffer->gameEvent.droppedCount += dropCount;
    ++inputBuffer->gameEvent.dropsDone;

    return true;
}

