#ifndef IG20260408232415
#define IG20260408232415

#include "ActionTypeId.h"
#include "Command.h"
#include "CommandValidation.h"
#include "Game.h"
#include "PlayerId.h"
#include <stdbool.h>
#include <unity.h>

void testvalidateCommandActionType( void )
{
    Command command = newCommand();
    Game game = newGame( 5 );

    command.playerId = PLAYER_WHITE;

    TEST_ASSERT_EQUAL_INT( false, validateCommandActionType( &command, &game ) );

    command.actionType = ACTION_TYPE_PLACE;
    TEST_ASSERT_EQUAL_INT( true, validateCommandActionType( &command, &game ) );

    command.actionType = ACTION_TYPE_LIFT;
    TEST_ASSERT_EQUAL_INT( true, validateCommandActionType( &command, &game ) );
}

void testvalidateCommandStoneType( void )
{
    Command command = newCommand();
    Game game = newGame( 5 );

    command.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( true, validateCommandStoneType( &command, &game ) );

    command.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( true, validateCommandStoneType( &command, &game ) );

    command.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( true, validateCommandStoneType( &command, &game ) );

    game.reserves.regular[PLAYER_WHITE] = 0;
    game.reserves.capstone[PLAYER_WHITE] = 0;

    command.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( false, validateCommandStoneType( &command, &game ) );

    command.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( false, validateCommandStoneType( &command, &game ) );

    command.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( false, validateCommandStoneType( &command, &game ) );
}

void testValidateCommand( void )
{
    Command command = newCommand();
    Game game = newGame( 5 );

    command.state = STATE_GET_ACTION_TYPE;
    command.playerId = PLAYER_WHITE;

    TEST_ASSERT_EQUAL_INT( false, validateCommandActionType( &command, &game ) );

    command.actionType = ACTION_TYPE_PLACE;
    TEST_ASSERT_EQUAL_INT( true, validateCommandActionType( &command, &game ) );

    command.actionType = ACTION_TYPE_LIFT;
    TEST_ASSERT_EQUAL_INT( true, validateCommandActionType( &command, &game ) );

    command.state = STATE_GET_STONE_TYPE;
    command.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( true, validateCommandStoneType( &command, &game ) );

    command.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( true, validateCommandStoneType( &command, &game ) );

    command.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( true, validateCommandStoneType( &command, &game ) );

    game.reserves.regular[PLAYER_WHITE] = 0;
    game.reserves.capstone[PLAYER_WHITE] = 0;

    command.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( false, validateCommandStoneType( &command, &game ) );

    command.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( false, validateCommandStoneType( &command, &game ) );

    command.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( false, validateCommandStoneType( &command, &game ) );
}

#endif
