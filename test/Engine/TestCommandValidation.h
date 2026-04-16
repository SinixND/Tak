#ifndef IG20260408232415
#define IG20260408232415

#include "ActionTypeId.h"
#include "Command.h"
#include "CommandValidation.h"
#include "Game.h"
#include "PlayerId.h"
#include <stdbool.h>
#include <unity.h>

void testValidateInputActionType( void )
{
    Command command = newCommand();
    Game game = newGame( 5 );

    command.playerId = PLAYER_WHITE;

    TEST_ASSERT_EQUAL_INT( false, validateInputActionType( &command, &game ) );

    command.actionType = ACTION_TYPE_PLACE;
    TEST_ASSERT_EQUAL_INT( true, validateInputActionType( &command, &game ) );

    command.actionType = ACTION_TYPE_LIFT;
    TEST_ASSERT_EQUAL_INT( true, validateInputActionType( &command, &game ) );
}

void testValidateInputStoneType( void )
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

void testValidateCommand( void )
{
    Command command = newCommand();

    switch ( pCommand->state )
    {
        case STATE_GET_ACTION_TYPE:
        {
            return validateInputActionType(
                pCommand,
                pGame
            );
        }

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

#endif
