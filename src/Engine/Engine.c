#include "Engine.h"

#include "ActionTypeId.h"
#include "Command.h"
#include "CommandStateId.h"
#include "CommandValidation.h"
#include "DirectionId.h"
#include "Event.h"
#include "FileId.h"
#include "Game.h"
#include "History.h"
#include "InputBuffer.h"
#include "InputParsing.h"
#include "Position.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

bool autocompleteCommand(
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

    if ( !( pCommand->state == COMMAND_STATE_GET_FIRST_DROP_AMOUNT
            || pCommand->state == COMMAND_STATE_GET_DROP_AMOUNT ) )
    {
        return false;
    }

    FileId const nextFileX
        = pCommand->fileX
          + ( getOffsetX( pCommand->direction )
              * ( pCommand->drops
                  + 1 ) );

    RankId const nextRankY
        = pCommand->rankY
          + ( getOffsetY( pCommand->direction )
              * ( pCommand->drops
                  + 1 ) );

    /// Need to drop all if next square out of board
    if (
        ( nextFileX < 0 )
        || ( nextFileX >= pGame->board.size )
        || ( nextRankY < 0 )
        || ( nextRankY >= pGame->board.size )
    )
    {
        pCommand->dropCounts[pCommand->drops] = pGame->stackBuffer.stoneCount;
        pCommand->state = COMMAND_STATE_GET_ACTION_TYPE;

        return true;
    }

    int const nextSquareIdx = positionToSquare(
        nextFileX,
        nextRankY,
        pGame->board.size
    );

    /// Drop nothing at source square if liftcount == 1
    if ( pCommand->drops < 1
         && pGame->stackBuffer.stoneCount == 1 )
    {
        pCommand->dropCounts[pCommand->drops] = 0;
        pCommand->state = COMMAND_STATE_GET_DROP_AMOUNT;

        return true;
    }

    /// Need to drop 'all' if not first drop and only one stone left in stack buffer
    if ( pCommand->drops > 0
         && pGame->stackBuffer.stoneCount == 1 )
    {
        pCommand->dropCounts[pCommand->drops] = 1;
        pCommand->state = COMMAND_STATE_GET_ACTION_TYPE;

        return true;
    }

    /// Need to drop all if next squares type is capstone
    if ( pGame->board.stackTypes[nextSquareIdx] == STONE_TYPE_CAP )
    {
        pCommand->dropCounts[pCommand->drops] = pGame->stackBuffer.stoneCount;
        pCommand->state = COMMAND_STATE_GET_ACTION_TYPE;

        return true;
    }

    /// Need to drop all if next squares type is standing and buffer type is not capstone
    if ( pGame->board.stackTypes[nextSquareIdx] == STONE_TYPE_STANDING
         && pGame->stackBuffer.stackType != STONE_TYPE_CAP )
    {
        pCommand->dropCounts[pCommand->drops] = pGame->stackBuffer.stoneCount;
        pCommand->state = COMMAND_STATE_GET_ACTION_TYPE;

        return true;
    }

    /// Need to drop all but one if next squares type is standing and buffer type is capstone
    if ( pGame->board.stackTypes[nextSquareIdx] == STONE_TYPE_STANDING
         && pGame->stackBuffer.stackType == STONE_TYPE_CAP )
    {
        pCommand->dropCounts[pCommand->drops] = pGame->stackBuffer.stoneCount - 1;

        return true;
    }

    return false;
}

void buildCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    Game const* const pGame
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
        pGame
        && "Pointer is nullptr"
    );

    /// Temporary command
    Command command = *pCommand;

    /// Set command value from input
    if ( !parseInput(
             &command,
             pInputBuffer
         ) )
    {
        return;
    }

    /// Validate input against game
    if ( !validateCommand(
             &command,
             pGame
         ) )
    {
        /// Reset original command to query for file if rank invalid
        if ( command.state == COMMAND_STATE_GET_RANK_Y )
        {
            pCommand->fileX = FILE_NONE;
            pCommand->state = COMMAND_STATE_GET_FILE_X;
        }

        return;
    }

    /// Update command state
    setNextCommandState(
        &command,
        pGame
    );

    /// Copy temp command to original
    *pCommand = command;
}

void buildEvent(
    Event* const pEvent,
    Command const* const pCommand,
    int const boardSize
)
{
    assert(
        pEvent
        && "Pointer is nullptr"
    );

    assert(
        pCommand
        && "Pointer is nullptr"
    );

    assert(
        ( boardSize >= BOARD_SIZE_MIN )
        && ( boardSize <= BOARD_SIZE_MAX )
        && "Board size invalid"
    );

    pEvent->actionType = pCommand->actionType;
    pEvent->playerId = pCommand->playerId;
    pEvent->stoneType = pCommand->stoneType;
    pEvent->squareIdx
        = ( ( pCommand->fileX + pCommand->rankY ) < 0 )
              ? -1
              : positionToSquare(
                    pCommand->fileX + ( getOffsetX( pCommand->direction ) * pCommand->drops ),
                    pCommand->rankY + ( getOffsetY( pCommand->direction ) * pCommand->drops ),
                    boardSize
                );

    pEvent->dropCount = pCommand->dropCounts[pCommand->drops];
}

void recordEvent(
    History* const pHistory,
    Event const* const pEvent,
    Game const* const pGame
)
{
    Record* const pRecord = &pHistory->records[pHistory->recordIdx];

    pRecord->actionType = pEvent->actionType;

    switch ( pRecord->actionType )
    {
        case ACTION_TYPE_PLACE:
        {
            pRecord->Data.place.stoneType = pEvent->stoneType;

            pRecord->Data.place.playerId = pEvent->playerId;

            pRecord->Data.place.squareIdx = pEvent->squareIdx;

            break;
        }

        case ACTION_TYPE_LIFT:
        {
            pRecord->Data.lift.squareIdx = pEvent->squareIdx;

            break;
        }

        case ACTION_TYPE_DROP:
        {
            pRecord->Data.drop.squareIdx = pEvent->squareIdx;

            pRecord->Data.drop.dropCount = pEvent->dropCount;

            pRecord->Data.drop.flattened
                = ( pGame->board.stackTypes[pEvent->squareIdx]
                    == STONE_TYPE_STANDING );

            break;
        }

        default:
            return;
    }

    ++pHistory->recordIdx;
}

