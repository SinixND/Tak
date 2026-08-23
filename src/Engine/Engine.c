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
#include "InputId.h"
#include "InputParsing.h"
#include "PlayerId.h"
#include "Position.h"
#include "RankId.h"
#include "Record.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

bool setBoardSize(
    Game* const pGame,
    InputBuffer const* const pInputBuffer
)
{
    assert(
        pInputBuffer
        && "Pointer is nullptr"
    );

    assert(
        pGame
        && "Pointer is nullptr"
    );

    switch ( getCommandId(
        pInputBuffer,
        CONTEXT_SIZE
    ) )
    {
        case COMMAND_CONFIRM:
        {
            *pGame = newGame( BOARD_SIZE_DEFAULT );
            return true;
        }

        case COMMAND_3:
        {
            *pGame = newGame( 3 );
            return true;
        }

        case COMMAND_4:
        {
            *pGame = newGame( 4 );
            return true;
        }

        case COMMAND_5:
        {
            *pGame = newGame( 5 );
            return true;
        }

        case COMMAND_6:
        {
            *pGame = newGame( 6 );
            return true;
        }

        case COMMAND_7:
        {
            *pGame = newGame( 7 );
            return true;
        }

        case COMMAND_8:
        {
            *pGame = newGame( 8 );
            return true;
        }

        default:
            return false;
    }
}

bool autocompleteAction(
    Command* const pCommand,
    Game const* const pGame
);

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
        case COMMAND_STATE_DEFAULT:
        {
            return autocompleteAction(
                pCommand,
                pGame
            );
        }

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

bool autocompleteAction(
    Command* const pCommand,
    Game const* const pGame
)
{
    /// Return if required input not met
    if (
        pCommand->fileX == FILE_NONE
        || pCommand->rankY == RANK_NONE
        || pCommand->actionType != ACTION_TYPE_NONE
    )
    {
        return false;
    }

    /// Deduce action type from target position
    PlayerId targetStackId
        = pGame->board.stackIds[positionToSquare(
            pCommand->fileX,
            pCommand->rankY,
            pGame->board.size
        )];

    /// Update command depending on who owns the targeted square
    if ( targetStackId == PLAYER_NONE )
    {
        pCommand->actionType = ACTION_TYPE_PLACE;
        /// Default to stone type FLAT if not set
        pCommand->stoneType
            = ( pCommand->stoneType == STONE_TYPE_NONE )
                  ? STONE_TYPE_FLAT
                  : pCommand->stoneType;

        return true;
    }
    else if ( targetStackId == pGame->activePlayer )
    {
        pCommand->actionType = ACTION_TYPE_LIFT;
        pCommand->state = COMMAND_STATE_GET_DIRECTION;

        return true;
    }

    return false;
}

bool autocompleteDrop(
    Command* const pCommand,
    Game const* const pGame
)
{
    /// Complete drop action if bufferedDropCount >= stackBuffer size
    if ( pCommand->bufferedDropCount >= pGame->stackBuffer.stoneCount )
    {
        pCommand->dropCounts[pCommand->drops] = pCommand->bufferedDropCount;
        /// TODO: Delete/Required?
        // pCommand->state = COMMAND_STATE_DEFAULT;

        return true;
    }

    /// Can not drop all on source square: Complete if bufferedDropCount >= stackBuffer size - 1 on origin square
    if (
        pCommand->bufferedDropCount > 0
        && pCommand->bufferedDropCount >= pGame->stackBuffer.stoneCount - 1
        && !pCommand->drops
    )
    {
        pCommand->dropCounts[pCommand->drops] = pCommand->bufferedDropCount;
        pCommand->bufferedDropCount = 1;

        return true;
    }

    /// Need to drop all if next square out of board
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

    if (
        ( nextFileX < 0 )
        || ( nextFileX >= pGame->board.size )
        || ( nextRankY < 0 )
        || ( nextRankY >= pGame->board.size )
    )
    {
        pCommand->dropCounts[pCommand->drops] = pGame->stackBuffer.stoneCount;
        pCommand->state = COMMAND_STATE_DEFAULT;

        return true;
    }

    /// Drop nothing at source square if single pickup
    if ( pCommand->drops < 1
         && pCommand->dropCounts[pCommand->drops] < 0
         && pGame->stackBuffer.stoneCount == 1 )
    {
        pCommand->dropCounts[pCommand->drops] = 0;
        pCommand->state = COMMAND_STATE_GET_DROP_AMOUNT;

        return true;
    }

    /// Need to drop 'all' if not first drop and only one stone left in stack buffer
    if ( pCommand->drops > 0
         && pCommand->dropCounts[pCommand->drops] < 0
         && pGame->stackBuffer.stoneCount == 1 )
    {
        pCommand->dropCounts[pCommand->drops] = 1;
        pCommand->state = COMMAND_STATE_DEFAULT;

        return true;
    }

    /// Need to drop all if next squares type is capstone
    int const nextSquareIdx = positionToSquare(
        nextFileX,
        nextRankY,
        pGame->board.size
    );

    if ( pGame->board.stackTypes[nextSquareIdx] == STONE_TYPE_CAP )
    {
        pCommand->dropCounts[pCommand->drops] = pGame->stackBuffer.stoneCount;
        pCommand->state = COMMAND_STATE_DEFAULT;

        return true;
    }

    /// Need to drop all if next squares type is standing and buffer type is not capstone
    if ( pGame->board.stackTypes[nextSquareIdx] == STONE_TYPE_STANDING
         && pGame->stackBuffer.stackType != STONE_TYPE_CAP )
    {
        pCommand->dropCounts[pCommand->drops] = pGame->stackBuffer.stoneCount;
        pCommand->state = COMMAND_STATE_DEFAULT;

        return true;
    }

    /// Need to drop all but one if
    /// - next squares type is standing
    /// - buffer type is capstone
    // TODO: Required/delete?
    /// - this is the first drop
    if ( pGame->board.stackTypes[nextSquareIdx] == STONE_TYPE_STANDING
         && pGame->stackBuffer.stackType == STONE_TYPE_CAP
         // TODO: Required/delete?
         // && !pCommand->drops
    )
    {
        pCommand->dropCounts[pCommand->drops] = pGame->stackBuffer.stoneCount - 1;

        return true;
    }

    return false;
}

bool buildCommand(
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

    /// Make a temporary command
    Command command = *pCommand;

    /// Set context-dependent command value from input
    if ( !updateCommandFromInput(
             &command,
             pInputBuffer,
             pGame->board.size
         ) )
    {
        return false;
    }

    /// Validate input against game
    if ( !validateCommand(
             &command,
             pGame
         ) )
    {
        /// Reset original command position if invalid
        pCommand->fileX
            = ( pCommand->rankY == RANK_NONE )
                  ? FILE_NONE
                  : pCommand->fileX;

        pCommand->rankY = RANK_NONE;

        /// Keep buffered stone count
        pCommand->bufferedDropCount = command.bufferedDropCount;

        return false;
    }

    /// Update command state
    setNextCommandState(
        &command,
        pGame
    );

    /// Copy temp command to original
    *pCommand = command;

    return true;
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

    /// Prevent undo opening
    if ( pHistory->lastRecordIdx < 3 )
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

            --pHistory->lastRecordIdx;

            /// Turn complete
            pGame->activePlayer
                = ( pGame->activePlayer == PLAYER_WHITE )
                      ? PLAYER_BLACK
                      : PLAYER_WHITE;

            break;
        }

        case ACTION_TYPE_LIFT:
        {
            /// Undo lift
            dropStack(
                pGame,
                pHistory->records[pHistory->lastRecordIdx].Data.lift.squareIdx
            );

            --pHistory->lastRecordIdx;

            /// Undo turn complete
            pGame->activePlayer
                = ( pGame->activePlayer == PLAYER_WHITE )
                      ? PLAYER_BLACK
                      : PLAYER_WHITE;

            break;
        }

        case ACTION_TYPE_DROP:
        {
            /// Undo all drop events of the turn
            while ( pHistory->records[pHistory->lastRecordIdx].actionType == ACTION_TYPE_DROP )
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

                --pHistory->lastRecordIdx;
            }

            /// Undo lift that started the turn and preceeded the drops
            dropStack(
                pGame,
                pHistory->records[pHistory->lastRecordIdx].Data.lift.squareIdx
            );

            --pHistory->lastRecordIdx;

            /// Undo turn complete
            pGame->activePlayer
                = ( pGame->activePlayer == PLAYER_WHITE )
                      ? PLAYER_BLACK
                      : PLAYER_WHITE;

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

            /// Redo turn complete
            pGame->activePlayer
                = ( pGame->activePlayer == PLAYER_WHITE )
                      ? PLAYER_BLACK
                      : PLAYER_WHITE;

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
            while ( pHistory->records[pHistory->lastRecordIdx + 1].actionType == ACTION_TYPE_DROP )
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
            while ( pHistory->records[pHistory->lastRecordIdx + 1].actionType == ACTION_TYPE_DROP )
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

            /// Redo turn complete
            pGame->activePlayer
                = ( pGame->activePlayer == PLAYER_WHITE )
                      ? PLAYER_BLACK
                      : PLAYER_WHITE;

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
            while ( pHistory->records[pHistory->lastRecordIdx].actionType == ACTION_TYPE_DROP )
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

