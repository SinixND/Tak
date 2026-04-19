#include "Engine.h"

#include "Command.h"
#include "CommandValidation.h"
#include "Event.h"
#include "Game.h"
#include "InputBuffer.h"
#include "InputParsing.h"
#include "Position.h"
#include <assert.h>
#include <stdbool.h>

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
