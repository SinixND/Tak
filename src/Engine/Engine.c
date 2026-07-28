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
#include "Record.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

bool autocompleteDrop(
    Command* const pCommand,
    Game const* const pGame
);

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

    switch ( pCommand->state )
    {
        case COMMAND_STATE_GET_FIRST_DROP_AMOUNT:
        case COMMAND_STATE_GET_DROP_AMOUNT:
        {
            return autocompleteDrop(
                pCommand,
                pGame
            );
        }

        default:
            return false;
    }
}

bool autocompleteDrop(
    Command* const pCommand,
    Game const* const pGame
)
{
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
        pCommand->state = COMMAND_STATE_GET_FIRST_INPUT;

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
        pCommand->state = COMMAND_STATE_GET_FIRST_INPUT;

        return true;
    }

    /// Need to drop all if next squares type is capstone
    if ( pGame->board.stackTypes[nextSquareIdx] == STONE_TYPE_CAP )
    {
        pCommand->dropCounts[pCommand->drops] = pGame->stackBuffer.stoneCount;
        pCommand->state = COMMAND_STATE_GET_FIRST_INPUT;

        return true;
    }

    /// Need to drop all if next squares type is standing and buffer type is not capstone
    if ( pGame->board.stackTypes[nextSquareIdx] == STONE_TYPE_STANDING
         && pGame->stackBuffer.stackType != STONE_TYPE_CAP )
    {
        pCommand->dropCounts[pCommand->drops] = pGame->stackBuffer.stoneCount;
        pCommand->state = COMMAND_STATE_GET_FIRST_INPUT;

        return true;
    }

    /// Need to drop all but one if
    /// - next squares type is standing
    /// - buffer type is capstone
    /// - this is the first drop
    if ( pGame->board.stackTypes[nextSquareIdx] == STONE_TYPE_STANDING
         && pGame->stackBuffer.stackType == STONE_TYPE_CAP
         && !pCommand->drops )
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
             pInputBuffer,
             pGame
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

void recordCommand(
    History* const pHistory,
    Command const* const pCommand,
    Game const* const pGame
)
{
    assert(
        pHistory
        && "Pointer is nullptr"
    );

    assert(
        pCommand
        && "Pointer is nullptr"
    );

    assert(
        pGame
        && "Pointer is nullptr"
    );

    pHistory->commands[pHistory->lastCommandIdx + 1] = *pCommand;

    ++pHistory->lastCommandIdx;
    pHistory->totalCommands = pHistory->lastCommandIdx;
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
    assert(
        pHistory
        && "Pointer is nullptr"
    );

    assert(
        pEvent
        && "Pointer is nullptr"
    );

    assert(
        pGame
        && "Pointer is nullptr"
    );

    Record* const pNewRecord = &pHistory->records[pHistory->lastRecordIdx + 1];

    pNewRecord->actionType = pEvent->actionType;

    switch ( pNewRecord->actionType )
    {
        case ACTION_TYPE_PLACE:
        {
            pNewRecord->Data.place.stoneType = pEvent->stoneType;

            pNewRecord->Data.place.playerId = pEvent->playerId;

            pNewRecord->Data.place.squareIdx = pEvent->squareIdx;

            break;
        }

        case ACTION_TYPE_LIFT:
        {
            pNewRecord->Data.lift.squareIdx = pEvent->squareIdx;

            break;
        }

        case ACTION_TYPE_DROP:
        {
            pNewRecord->Data.drop.squareIdx = pEvent->squareIdx;

            pNewRecord->Data.drop.dropCount = pEvent->dropCount;

            pNewRecord->Data.drop.flattened
                = ( pGame->board.stackTypes[pEvent->squareIdx]
                    == STONE_TYPE_STANDING );

            break;
        }

        default:
            return;
    }

    ++pHistory->lastRecordIdx;
    pHistory->totalRecords = pHistory->lastRecordIdx;
}

void undoTurn(
    History* const pHistory,
    Game* const pGame
)
{
    assert(
        pHistory
        && "Pointer is nullptr"
    );

    assert(
        pGame
        && "Pointer is nullptr"
    );

    /// Cant undo opening
    if ( pHistory->lastRecordIdx < 2 )
    {
        return;
    }

    switch ( pHistory->records[pHistory->lastRecordIdx].actionType )
    {
        case ACTION_TYPE_PLACE:
        {
            /// Undo place
            takeStone(
                pGame,
                pHistory->records[pHistory->lastRecordIdx].Data.place.squareIdx
            );

            /// Step back in history
            --pHistory->lastRecordIdx;

            /// Place always started a turn: done
            break;
        }

        case ACTION_TYPE_LIFT:
        {
            /// Undo lift
            dropStack(
                pGame,
                pHistory->records[pHistory->lastRecordIdx].Data.lift.squareIdx
            );

            /// Step back in history
            --pHistory->lastRecordIdx;

            /// Lift always started a turn: done
            break;
        }

        case ACTION_TYPE_DROP:
        {
            /// Undo all drop events of the turn
            while (
                pHistory->records[pHistory->lastRecordIdx].actionType
                == ACTION_TYPE_DROP
            )
            {
                DataDrop const dataDrop
                    = pHistory->records[pHistory->lastRecordIdx].Data.drop;

                /// Undo all single stone drops of this drop event
                for ( int n = 0; n < dataDrop.dropCount; ++n )
                {
                    /// Undo single stone drop
                    liftStone(
                        pGame,
                        dataDrop.squareIdx,
                        dataDrop.flattened
                    );
                }

                /// Step back in history ('while action == drop')
                --pHistory->lastRecordIdx;
            }

            /// Undo lift that started the turn and preceeded the drops
            dropStack(
                pGame,
                pHistory->records[pHistory->lastRecordIdx].Data.lift.squareIdx
            );

            /// Step back in history
            --pHistory->lastRecordIdx;

            break;
        }

        default:
            return;
    }

    --pHistory->lastCommandIdx;
}

void redoTurn(
    History* const pHistory,
    Game* const pGame
)
{
    assert(
        pHistory
        && "Pointer is nullptr"
    );

    assert(
        pGame
        && "Pointer is nullptr"
    );

    switch ( pHistory->records[pHistory->lastRecordIdx + 1].actionType )
    {
        case ACTION_TYPE_PLACE:
        {
            DataPlace const dataPlace
                = pHistory->records[pHistory->lastRecordIdx + 1].Data.place;

            placeStone(
                pGame,
                dataPlace.playerId,
                dataPlace.squareIdx,
                dataPlace.stoneType
            );

            ++pHistory->lastRecordIdx;

            break;
        }

        case ACTION_TYPE_LIFT:
        {
            liftStack(
                pGame,
                pHistory->records[pHistory->lastRecordIdx + 1].Data.lift.squareIdx
            );

            ++pHistory->lastRecordIdx;

            /// Redo drop action until turn finished
            while (
                pHistory->records[pHistory->lastRecordIdx + 1].actionType
                == ACTION_TYPE_DROP
            )
            {
                DataDrop const dataDrop
                    = pHistory->records[pHistory->lastRecordIdx + 1].Data.drop;

                for ( int n = 0; n < dataDrop.dropCount; ++n )
                {
                    dropStone(
                        pGame,
                        dataDrop.squareIdx
                    );
                }

                ++pHistory->lastRecordIdx;
            }

            break;
        }

        case ACTION_TYPE_DROP:
        {
            /// Redo drop action until turn finished
            while (
                pHistory->records[pHistory->lastRecordIdx + 1].actionType
                == ACTION_TYPE_DROP
            )
            {
                DataDrop const dataDrop
                    = pHistory->records[pHistory->lastRecordIdx + 1].Data.drop;

                for ( int n = 0; n < dataDrop.dropCount; ++n )
                {
                    dropStone(
                        pGame,
                        dataDrop.squareIdx
                    );
                }

                ++pHistory->lastRecordIdx;
            }

            break;
        }

        default:
            return;
    }

    ++pHistory->lastCommandIdx;
}

void resetTurn(
    Command* const pCommand,
    History* const pHistory,
    Game* const pGame
)
{
    assert(
        pCommand
        && "Pointer is nullptr"
    );

    assert(
        pHistory
        && "Pointer is nullptr"
    );

    assert(
        pGame
        && "Pointer is nullptr"
    );

    if ( !(
             pCommand->state == COMMAND_STATE_GET_DIRECTION
             || pCommand->state == COMMAND_STATE_GET_FIRST_DROP_AMOUNT
             || pCommand->state == COMMAND_STATE_GET_DROP_AMOUNT
         ) )
    {
        return;
    }

    switch ( pHistory->records[pHistory->lastRecordIdx].actionType )
    {
        case ACTION_TYPE_LIFT:
        {
            /// Undo lift
            dropStack(
                pGame,
                pHistory->records[pHistory->lastRecordIdx].Data.lift.squareIdx
            );

            /// Remove records of incomplete turn
            pHistory->records[pHistory->lastRecordIdx] = newRecord();

            /// Step back in history
            --pHistory->lastRecordIdx;
            --pHistory->totalRecords;

            /// Lift always started a turn: done
            return;
        }

        case ACTION_TYPE_DROP:
        {
            /// Undo all drop events of the turn
            while (
                pHistory->records[pHistory->lastRecordIdx].actionType
                == ACTION_TYPE_DROP
            )
            {
                DataDrop const dataDrop
                    = pHistory->records[pHistory->lastRecordIdx].Data.drop;

                /// Undo all single stone drops of this drop event
                for ( int n = 0; n < dataDrop.dropCount; ++n )
                {
                    /// Undo single stone drop
                    liftStone(
                        pGame,
                        dataDrop.squareIdx,
                        dataDrop.flattened
                    );
                }

                /// Remove records of incomplete turn
                pHistory->records[pHistory->lastRecordIdx] = newRecord();

                /// Step back in history
                --pHistory->lastRecordIdx;
                --pHistory->totalRecords;
            }

            /// Undo lift that started the turn and preceeded the drops
            dropStack(
                pGame,
                pHistory->records[pHistory->lastRecordIdx].Data.lift.squareIdx
            );

            /// Remove records of incomplete turn
            pHistory->records[pHistory->lastRecordIdx] = newRecord();

            /// Step back in history
            --pHistory->lastRecordIdx;
            --pHistory->totalRecords;

            /// Lift always started a turn: done
            return;
        }

        default:
            return;
    }
}

