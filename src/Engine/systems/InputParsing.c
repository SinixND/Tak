#include "InputParsing.h"

#include "ActionTypeId.h"
#include "BackendInterface.h"
#include "CommandId.h"
#include "CommandStateId.h"
#include "DirectionId.h"
#include "FileId.h"
#include "InputBuffer.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

bool updateCommandFromInput(
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
        case COMMAND_STATE_DEFAULT:
        {
            return parseDefaultInputToCommand(
                pCommand,
                pInputBuffer,
                boardSize
            );
        }

        case COMMAND_STATE_GET_POSITION:
        {
            return parsePositionInputToCommand(
                pCommand,
                pInputBuffer,
                boardSize
            );
        }

        case COMMAND_STATE_GET_DIRECTION:
        {
            return parseDirectionInputToCommand(
                pCommand,
                pInputBuffer,
                boardSize
            );
        }

        case COMMAND_STATE_GET_FIRST_DROP_AMOUNT:
        {
            return parseFirstDropAmountInputToCommand(
                pCommand,
                pInputBuffer,
                boardSize
            );
        }

        case COMMAND_STATE_GET_DROP_AMOUNT:
        {
            return parseDropAmountInputToCommand(
                pCommand,
                pInputBuffer,
                boardSize
            );
        }

        default:
            return false;
    }
}

bool parseDefaultInputToCommand(
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
        CONTEXT_INPUT_DEFAULT
    ) )
    {
        case COMMAND_POSITION:
        {
            Tile tile = getTile(
                pInputBuffer->mousePosition[0],
                pInputBuffer->mousePosition[1],
                boardSize
            );

            pCommand->fileX = tile.fileX;
            pCommand->rankY = tile.rankY;

            return true;
        }

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
            pCommand->stoneType = ( pCommand->stoneType % ( 2 + ( boardSize > 4 ) ) ) + 1;

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

        case COMMAND_1:
        {
            pCommand->rankY = RANK_1;

            return true;
        }

        case COMMAND_2:
        {
            pCommand->rankY = RANK_2;

            return true;
        }

        case COMMAND_3:
        {
            pCommand->rankY = RANK_3;

            return true;
        }

        case COMMAND_4:
        {
            pCommand->rankY = RANK_4;

            return true;
        }

        case COMMAND_5:
        {
            pCommand->rankY = RANK_5;

            return true;
        }

        case COMMAND_6:
        {
            pCommand->rankY = RANK_6;

            return true;
        }

        case COMMAND_7:
        {
            pCommand->rankY = RANK_7;

            return true;
        }

        case COMMAND_8:
        {
            pCommand->rankY = RANK_8;

            return true;
        }

        default:
            return false;
    }
}

bool parsePositionInputToCommand(
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
        CONTEXT_POSITION
    ) )
    {
        case COMMAND_POSITION:
        {
            Tile tile = getTile(
                pInputBuffer->mousePosition[0],
                pInputBuffer->mousePosition[1],
                boardSize
            );

            pCommand->fileX = tile.fileX;
            pCommand->rankY = tile.rankY;

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

        case COMMAND_1:
        {
            pCommand->rankY = RANK_1;

            return true;
        }

        case COMMAND_2:
        {
            pCommand->rankY = RANK_2;

            return true;
        }

        case COMMAND_3:
        {
            pCommand->rankY = RANK_3;

            return true;
        }

        case COMMAND_4:
        {
            pCommand->rankY = RANK_4;

            return true;
        }

        case COMMAND_5:
        {
            pCommand->rankY = RANK_5;

            return true;
        }

        case COMMAND_6:
        {
            pCommand->rankY = RANK_6;

            return true;
        }

        case COMMAND_7:
        {
            pCommand->rankY = RANK_7;

            return true;
        }

        case COMMAND_8:
        {
            pCommand->rankY = RANK_8;

            return true;
        }

        default:
            return false;
    }
}

bool parseDirectionInputToCommand(
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
        CONTEXT_DIRECTION
    ) )
    {
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

        case COMMAND_POSITION:
        {
            Tile mouseTile = getTile(
                pInputBuffer->mousePosition[0],
                pInputBuffer->mousePosition[1],
                boardSize
            );

            int const offset[2] = {
                mouseTile.fileX - pCommand->fileX,
                mouseTile.rankY - pCommand->rankY
            };

            if ( !offset[0]
                 && !offset[1] )
            {
                return false;
            }

            pCommand->direction
                = ( ( offset[0] * offset[0] ) > ( offset[1] * offset[1] ) )
                      ? ( ( offset[0] < 0 )
                              ? DIR_LEFT
                              : DIR_RIGHT )
                      : ( ( offset[1] < 0 )
                              ? DIR_DOWN
                              : DIR_UP );

            return true;
        }

        default:
        {
            return false;
        }
    }
}

bool parseFirstDropAmountInputToCommand(
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

    assert(
        !pCommand->currentDropIdx
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

            return true;
        }

        case COMMAND_1:
        {
            pCommand->dropCounts[0] = 1;

            return true;
        }

        case COMMAND_2:
        {
            pCommand->dropCounts[0] = 2;

            return true;
        }

        case COMMAND_3:
        {
            pCommand->dropCounts[0] = 3;

            return true;
        }

        case COMMAND_4:
        {
            pCommand->dropCounts[0] = 4;

            return true;
        }

        case COMMAND_5:
        {
            pCommand->dropCounts[0] = 5;

            return true;
        }

        case COMMAND_6:
        {
            pCommand->dropCounts[0] = 6;

            return true;
        }

        case COMMAND_7:
        {
            pCommand->dropCounts[0] = 7;

            return true;
        }

        case COMMAND_8:
        {
            pCommand->dropCounts[0] = 8;

            return true;
        }

        case COMMAND_POSITION:
        {
            Tile mouseTile = getTile(
                pInputBuffer->mousePosition[0],
                pInputBuffer->mousePosition[1],
                boardSize
            );

            /// If mouse == command position
            /// -> Drop one in place
            if (
                mouseTile.fileX == pCommand->fileX && mouseTile.rankY == pCommand->rankY
            )
            {
                ++pCommand->bufferedDropCount;

                return true;
            }
            /// If offset is matching next square in direction and no drops yet
            /// -> Drop none in place, goto next square and drop one
            else if (
                ( pCommand->fileX
                  + getOffsetX( pCommand->direction ) )
                    == mouseTile.fileX
                && ( pCommand->rankY
                     + getOffsetY( pCommand->direction ) )
                       == mouseTile.rankY
            )
            {
                pCommand->dropCounts[0]
                    = pCommand->bufferedDropCount;

                pCommand->bufferedDropCount = 1;

                return true;
            }

            return false;
        }

        default:
            return false;
    }
}

bool parseDropAmountInputToCommand(
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

    assert(
        pCommand->currentDropIdx > 0
        && "Drops value invalid"
    );

    switch ( getCommandId(
        pInputBuffer,
        CONTEXT_AMOUNT
    ) )
    {
        case COMMAND_1:
        {
            pCommand->dropCounts[pCommand->currentDropIdx] = 1;

            return true;
        }

        case COMMAND_2:
        {
            pCommand->dropCounts[pCommand->currentDropIdx] = 2;

            return true;
        }

        case COMMAND_3:
        {
            pCommand->dropCounts[pCommand->currentDropIdx] = 3;

            return true;
        }

        case COMMAND_4:
        {
            pCommand->dropCounts[pCommand->currentDropIdx] = 4;

            return true;
        }

        case COMMAND_5:
        {
            pCommand->dropCounts[pCommand->currentDropIdx] = 5;

            return true;
        }

        case COMMAND_6:
        {
            pCommand->dropCounts[pCommand->currentDropIdx] = 6;

            return true;
        }

        case COMMAND_7:
        {
            pCommand->dropCounts[pCommand->currentDropIdx] = 7;

            return true;
        }

        case COMMAND_8:
        case COMMAND_ALL:
        {
            pCommand->dropCounts[pCommand->currentDropIdx] = 8;

            return true;
        }

        case COMMAND_POSITION:
        {
            Tile mouseTile = getTile(
                pInputBuffer->mousePosition[0],
                pInputBuffer->mousePosition[1],
                boardSize
            );

            /// If mouse == command position + offset
            if (
                ( pCommand->fileX
                  + ( getOffsetX( pCommand->direction ) * pCommand->currentDropIdx ) )
                    == mouseTile.fileX
                && ( pCommand->rankY
                     + ( getOffsetY( pCommand->direction ) * pCommand->currentDropIdx ) )
                       == mouseTile.rankY
            )
            {
                ++pCommand->bufferedDropCount;

                return true;
            }
            /// If offset is matching next square direction
            else if (
                ( pCommand->fileX
                  + ( getOffsetX( pCommand->direction ) * ( pCommand->currentDropIdx + 1 ) ) )
                    == mouseTile.fileX
                && ( pCommand->rankY
                     + ( getOffsetY( pCommand->direction ) * ( pCommand->currentDropIdx + 1 ) ) )
                       == mouseTile.rankY
            )
            {
                pCommand->dropCounts[pCommand->currentDropIdx]
                    = pCommand->bufferedDropCount;

                pCommand->bufferedDropCount = 1;

                return true;
            }
        }
        default:
            return false;
    }
}

