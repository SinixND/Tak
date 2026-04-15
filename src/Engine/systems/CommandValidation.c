#include "CommandValidation.h"
#include "StoneTypeId.h"

bool validateCommand(
    Command* const pCommand,
    Game const* const pGame
)
{
    switch ( pCommand->state )
    {
        case STATE_GET_STONE_TYPE:
        {
            return validateInputStoneType(
                pCommand,
                pGame
            );
        }

        default:
            return false;
    }
}

bool validateInputStoneType(
    Command* const pCommand,
    Game const* const pGame
)
{
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
