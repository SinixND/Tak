#include "CommandValidation.h"

#include "ActionTypeId.h"
#include "DirectionId.h"
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
        ( pCommand->playerId == pGame->activePlayer )
        && ( pCommand->actionType == ACTION_TYPE_PLACE
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

    //* Sufficient reserves
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

    return (
        ( pCommand->rankY >= 0 )
        && ( pCommand->rankY < pGame->board.size )
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

    int const x = pCommand->fileX
                  + getOffsetX( pCommand->direction );

    int const y = pCommand->rankY
                  + getOffsetY( pCommand->direction );

    return ( x >= 0 )
           && ( x < pGame->board.size )
           && ( y >= 0 )
           && ( y < pGame->board.size );
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

