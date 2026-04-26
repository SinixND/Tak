#include "CommandValidation.h"

#include "ActionTypeId.h"
#include "DirectionId.h"
#include "Position.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

bool validateCommand(
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
        case STATE_GET_ACTION_TYPE:
        {
            return validateCommandActionType(
                pCommand,
                pGame
            );
        }

        case STATE_GET_STONE_TYPE:
        {
            return validateCommandStoneType(
                pCommand,
                pGame
            );
        }

        case STATE_GET_FILE_X:
        {
            return validateCommandFileX(
                pCommand,
                pGame
            );
        }

        case STATE_GET_RANK_Y:
        {
            return validateCommandRankY(
                pCommand,
                pGame
            );
        }

        case STATE_GET_DIRECTION:
        {
            return validateCommandDirection(
                pCommand,
                pGame
            );
        }

        case STATE_GET_FIRST_DROP_AMOUNT:
        case STATE_GET_DROP_AMOUNT:
        {
            /// Cap drop count
            if ( pCommand->dropCounts[pCommand->drops] > pGame->stackBuffer.stoneCount )
            {
                pCommand->dropCounts[pCommand->drops] = pGame->stackBuffer.stoneCount;
            }

            return validateCommandDropAmount(
                pCommand,
                pGame
            );
        }

        default:
            return false;
    }
}

bool validateCommandActionType(
    Command const* const pCommand,
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

    return (
        ( pCommand->actionType == ACTION_TYPE_PLACE
          || pCommand->actionType == ACTION_TYPE_LIFT )
    );
}

bool validateCommandStoneType(
    Command const* const pCommand,
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

    /// Sufficient reserves
    switch ( pCommand->stoneType )
    {
        case STONE_TYPE_FLAT:
        case STONE_TYPE_STANDING:
        {
            return pGame->reserves.regular[pCommand->playerId] > 0;
        }

        case STONE_TYPE_CAP:
        {
            return pGame->reserves.capstone[pCommand->playerId] > 0;
        }

        default:
            return false;
    }
}

bool validateCommandFileX(
    Command const* const pCommand,
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

    return (
        ( pCommand->fileX >= 0 )
        && ( pCommand->fileX < pGame->board.size )
    );
}

bool validateCommandRankY(
    Command const* const pCommand,
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

    if ( pCommand->rankY < 0
         || pCommand->fileX < 0 )
    {
        return false;
    }

    int const boardSize = pGame->board.size;
    int const squareIdx = positionToSquare( pCommand->fileX, pCommand->rankY, boardSize );
    int const stackIdx = squareToStackIndex( squareIdx, boardSize );

    return (
        ( pCommand->rankY >= 0 )
        && ( pCommand->rankY < pGame->board.size )
        && ( !pGame->board.stoneCounts[squareIdx]
             /// Player owns square
             || ( pGame->board.stoneIds[stackIdx + ( pGame->board.stoneCounts[squareIdx] - 1 )] )
                    == pCommand->playerId )
    );
}

bool validateCommandDirection(
    Command const* const pCommand,
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

    int const nextFileX
        = pCommand->fileX
          + getOffsetX( pCommand->direction );

    int const nextRankY
        = pCommand->rankY
          + getOffsetY( pCommand->direction );

    /// Next square must be on board
    if ( ( nextFileX < 0 )
         || ( nextFileX >= pGame->board.size )
         || ( nextRankY < 0 )
         || ( nextRankY >= pGame->board.size ) )
    {
        return false;
    }

    int const nextSquareIdx = positionToSquare(
        nextFileX,
        nextRankY,
        pGame->board.size
    );

    /// Next squares type must not be capstone
    if ( pGame->board.stackTypes[nextSquareIdx] == STONE_TYPE_CAP )
    {
        return false;
    }

    return true;
}

bool validateCommandDropAmount(
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

    // TODO: Checks required?
    return true;
}

