#include "CommandValidation.h"

#include "ActionTypeId.h"
#include "StoneTypeId.h"
#include <assert.h>

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

        default:
            return false;
    }
}

bool validateCommandActionType(
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

    return (
        ( pCommand->playerId == pGame->activePlayer )
        && ( pCommand->actionType == ACTION_TYPE_PLACE
             || pCommand->actionType == ACTION_TYPE_LIFT )
    );
}

bool validateCommandStoneType(
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
