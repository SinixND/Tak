#include "CommandValidation.h"

#include "ActionTypeId.h"
#include "DirectionId.h"
#include "FileId.h"
#include "PlayerId.h"
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
        case COMMAND_STATE_DEFAULT:
        {
            return validateCommandFirstInput(
                pCommand,
                pGame
            );
        }

        case COMMAND_STATE_GET_ACTION_TYPE:
        {
            return validateCommandActionType(
                pCommand,
                pGame
            );
        }

        case COMMAND_STATE_GET_STONE_TYPE:
        {
            return validateCommandStoneType(
                pCommand,
                pGame
            );
        }

        case COMMAND_STATE_GET_FILE_X:
        {
            return validateCommandFileX(
                pCommand,
                pGame
            );
        }

        case COMMAND_STATE_GET_RANK_Y:
        {
            return validateCommandRankY(
                pCommand,
                pGame
            );
        }

        case COMMAND_STATE_GET_DIRECTION:
        {
            return validateCommandDirection(
                pCommand,
                pGame
            );
        }

        case COMMAND_STATE_GET_FIRST_DROP_AMOUNT:
        case COMMAND_STATE_GET_DROP_AMOUNT:
        {
            /// Cap drop count
            if ( pCommand->dropCounts[pCommand->currentDropIdx] > pGame->stackBuffer.stoneCount )
            {
                pCommand->dropCounts[pCommand->currentDropIdx] = pGame->stackBuffer.stoneCount;
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

bool validateCommandFirstInput(
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

    bool isValid = true;

    if ( pCommand->actionType != ACTION_TYPE_NONE )
    {
        isValid &= validateCommandActionType(
            pCommand,
            pGame
        );
    }

    if ( pCommand->stoneType != STONE_TYPE_NONE )
    {
        isValid &= validateCommandStoneType(
            pCommand,
            pGame
        );
    }

    if ( pCommand->fileX != FILE_NONE )
    {
        isValid &= validateCommandFileX(
            pCommand,
            pGame
        );
    }

    if ( pCommand->rankY != RANK_NONE )
    {
        isValid &= validateCommandRankY(
            pCommand,
            pGame
        );
    }

    return isValid;
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

bool validateCommandPosition(
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

    int const boardSize = pGame->board.size;

    /// Verify fileX w/o rankY
    if (
        pCommand->fileX >= 0
        && ( pCommand->fileX < boardSize )
        && pCommand->rankY == RANK_NONE
    )
    {
        return true;
    }

    /// Verify valid input to positionToSquare()
    if (
        pCommand->fileX < 0
        || ( pCommand->fileX >= boardSize )
        || pCommand->rankY < 0
        || ( pCommand->rankY >= boardSize )
    )
    {
        return false;
    }

    int const squareIdx = positionToSquare( pCommand->fileX, pCommand->rankY, boardSize );

    PlayerId const stackId = pGame->board.stackIds[squareIdx];

    return (
        /// Player can place or lift
        ( stackId == pCommand->playerId
          || stackId == PLAYER_NONE )
        /// NOTE: Needed?
        // /// Place
        // || ( pCommand->actionType == ACTION_TYPE_PLACE
        //      && !pGame->board.stoneCounts[squareIdx] )
        // /// Lift
        // || ( pCommand->actionType == ACTION_TYPE_LIFT
        //      && pGame->board.stoneCounts[squareIdx]
        //      /// Player owns square
        //      && stackId == pCommand->playerId )
    );
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

    int const boardSize = pGame->board.size;

    /// Verify valid input to positionToSquare()
    if ( pCommand->rankY < 0
         || pCommand->fileX < 0
         || ( pCommand->fileX >= boardSize )
         || ( pCommand->rankY >= boardSize ) )
    {
        return false;
    }

    int const squareIdx = positionToSquare( pCommand->fileX, pCommand->rankY, boardSize );

    PlayerId const stackId = pGame->board.stackIds[squareIdx];

    return (
        ( pCommand->actionType == ACTION_TYPE_NONE
          && ( stackId == pCommand->playerId
               || stackId == PLAYER_NONE ) )
        /// Place
        || ( pCommand->actionType == ACTION_TYPE_PLACE
             && !pGame->board.stoneCounts[squareIdx] )
        /// Lift
        || ( pCommand->actionType == ACTION_TYPE_LIFT
             && pGame->board.stoneCounts[squareIdx]
             /// Player owns square
             && stackId == pCommand->playerId )
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

    FileId const nextFileX
        = pCommand->fileX
          + ( getOffsetX( pCommand->direction )
              * ( pCommand->currentDropIdx
                  + 1 ) );

    RankId const nextRankY
        = pCommand->rankY
          + ( getOffsetY( pCommand->direction )
              * ( pCommand->currentDropIdx
                  + 1 ) );

    if (
        ( nextFileX < 0 )
        || ( nextFileX >= pGame->board.size )
        || ( nextRankY < 0 )
        || ( nextRankY >= pGame->board.size )
    )
    {
        return false;
    }

    int const nextSquareIdx = positionToSquare(
        nextFileX,
        nextRankY,
        pGame->board.size
    );

    /// Return false if
    if (
        /// First drop count can be 0, must not drop all
        ( !pCommand->currentDropIdx
          && ( ( pCommand->dropCounts[pCommand->currentDropIdx] < 0 )
               || pCommand->dropCounts[pCommand->currentDropIdx] >= pGame->stackBuffer.stoneCount ) )
        /// Only first drop count can be 0
        || ( pCommand->currentDropIdx
             && ( ( pCommand->dropCounts[pCommand->currentDropIdx] < 1 )
                  || ( pCommand->dropCounts[pCommand->currentDropIdx] > pGame->stackBuffer.stoneCount ) ) )
        || ( pCommand->currentDropIdx < 0 )
        || ( pCommand->currentDropIdx >= pGame->board.size )
        /// Need to drop at least all but one if next drop can flatten
        || ( pCommand->dropCounts[pCommand->currentDropIdx] < ( pGame->stackBuffer.stoneCount - 1 )
             && ( pGame->board.stackTypes[nextSquareIdx] == STONE_TYPE_STANDING
                  && pGame->stackBuffer.stackType == STONE_TYPE_CAP ) )
    )
    {
        return false;
    }

    return true;
}

