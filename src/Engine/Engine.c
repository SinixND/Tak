#include "Engine.h"

#include "Command.h"
#include "CommandValidation.h"
#include "DirectionId.h"
#include "Event.h"
#include "FileId.h"
#include "Game.h"
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

    int const nextSquareIdx = positionToSquare(
        nextFileX,
        nextRankY,
        pGame->board.size
    );

    //* Need to drop 'all' if only one stone left in stack buffer
    if ( pGame->stackBuffer.stoneCount == 1 )
    {
        pCommand->dropCounts[pCommand->drops - 1] = 1;

        return true;
    }

    //* Need to drop all if next squares type is capstone
    if ( pGame->board.stackTypes[nextSquareIdx] == STONE_TYPE_CAP )
    {
        pCommand->dropCounts[pCommand->drops - 1] = pGame->stackBuffer.stoneCount;

        return true;
    }

    //* Need to drop all if next squares type is standing and buffer type is not capstone
    if ( pGame->board.stackTypes[nextSquareIdx] == STONE_TYPE_STANDING
         && pGame->stackBuffer.stoneType != STONE_TYPE_CAP )
    {
        pCommand->dropCounts[pCommand->drops - 1] = pGame->stackBuffer.stoneCount;

        return true;
    }

    //* Need to drop all but one if next squares type is standing and buffer type is capstone
    if ( pGame->board.stackTypes[nextSquareIdx] == STONE_TYPE_STANDING
         && pGame->stackBuffer.stoneType == STONE_TYPE_CAP )
    {
        pCommand->dropCounts[pCommand->drops - 1] = pGame->stackBuffer.stoneCount - 1;

        return true;
    }

    //* Need to drop all if next square out of board
    if (
        ( nextFileX < 0 )
        || ( nextFileX >= pGame->board.size )
        || ( nextRankY < 0 )
        || ( nextRankY >= pGame->board.size )
    )
    {
        pCommand->dropCounts[pCommand->drops - 1] = pGame->stackBuffer.stoneCount;

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
        pInputBuffer
        && "Pointer is nullptr"
    );

    //* Temporary command
    Command command = *pCommand;

    //* Set command value from input
    if ( !parseInput(
             &command,
             pInputBuffer
         ) )
    {
        return;
    }

    //* Cap drop count
    if ( command.dropCounts[command.drops - 1] > pGame->stackBuffer.stoneCount )
    {
        command.dropCounts[command.drops - 1] = pGame->stackBuffer.stoneCount;
    }

    //* Validate input against game
    if ( !validateCommand(
             &command,
             pGame
         ) )
    {
        return;
    }

    //* Update command
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
        ( boardSize > 2 )
        && "BoardSize too small"
    );

    assert(
        ( boardSize < 9 )
        && "BoardSize too big"
    );

    pEvent->actionType = pCommand->actionType;
    pEvent->playerId = pCommand->playerId;
    pEvent->stoneType = pCommand->stoneType;
    pEvent->squareIdx
        = ( ( pCommand->fileX + pCommand->rankY ) < 0 )
              ? -1
              : positionToSquare(
                    pCommand->fileX,
                    pCommand->rankY,
                    boardSize
                );

    pEvent->dropCount = pCommand->dropCounts[pCommand->drops - 1];
}
