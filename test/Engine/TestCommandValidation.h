#ifndef IG20260416174743
#define IG20260416174743

#include "ActionTypeId.h"
#include "Command.h"
#include "CommandStateId.h"
#include "CommandValidation.h"
#include "FileId.h"
#include "Game.h"
#include "PlayerId.h"
#include "RankId.h"
#include <stdbool.h>
#include <unity.h>

void testValidateCommandActionType( void )
{
    Command command = newCommand( PLAYER_WHITE );
    Game game = newGame( 5 );

    command.playerId = PLAYER_WHITE;

    TEST_ASSERT_EQUAL_INT( false, validateCommandActionType( &command, &game ) );

    command.actionType = ACTION_TYPE_PLACE;
    TEST_ASSERT_EQUAL_INT( true, validateCommandActionType( &command, &game ) );

    command.actionType = ACTION_TYPE_LIFT;
    TEST_ASSERT_EQUAL_INT( true, validateCommandActionType( &command, &game ) );
}

void testValidateCommandStoneType( void )
{
    Command command = newCommand( PLAYER_WHITE );
    Game game = newGame( 5 );

    command.playerId = PLAYER_WHITE;

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

void testValidateCommandFileX( void )
{
    Command command = newCommand( PLAYER_WHITE );
    Game game = newGame( 5 );

    command.fileX = FILE_NONE;
    TEST_ASSERT_EQUAL_INT( false, validateCommandFileX( &command, &game ) );

    command.fileX = FILE_A;
    TEST_ASSERT_EQUAL_INT( true, validateCommandFileX( &command, &game ) );

    command.fileX = FILE_E;
    TEST_ASSERT_EQUAL_INT( true, validateCommandFileX( &command, &game ) );

    command.fileX = FILE_F;
    TEST_ASSERT_EQUAL_INT( false, validateCommandFileX( &command, &game ) );
}

void testValidateCommandRankY( void )
{
    Command command = newCommand( PLAYER_WHITE );
    Game game = newGame( 5 );
    game.board.stoneCounts[0] = 1;

    command.actionType = ACTION_TYPE_PLACE;
    command.fileX = FILE_A;

    command.rankY = RANK_NONE;
    TEST_ASSERT_EQUAL_INT( false, validateCommandRankY( &command, &game ) );

    command.rankY = RANK_2;
    TEST_ASSERT_EQUAL_INT( true, validateCommandRankY( &command, &game ) );

    command.rankY = RANK_5;
    TEST_ASSERT_EQUAL_INT( true, validateCommandRankY( &command, &game ) );

    command.rankY = RANK_6;
    TEST_ASSERT_EQUAL_INT( false, validateCommandRankY( &command, &game ) );

    command.actionType = ACTION_TYPE_LIFT;

    command.rankY = RANK_1;
    TEST_ASSERT_EQUAL_INT( true, validateCommandRankY( &command, &game ) );
}

void testValidateCommandDirection( void )
{
    Command command = newCommand( PLAYER_WHITE );
    Game game = newGame( 5 );

    command.fileX = FILE_A;
    command.rankY = RANK_1;

    command.direction = DIR_NONE;
    TEST_ASSERT_EQUAL_INT( true, validateCommandDirection( &command, &game ) );

    command.direction = DIR_UP;
    TEST_ASSERT_EQUAL_INT( true, validateCommandDirection( &command, &game ) );
    command.direction = DIR_DOWN;
    TEST_ASSERT_EQUAL_INT( false, validateCommandDirection( &command, &game ) );
    command.direction = DIR_LEFT;
    TEST_ASSERT_EQUAL_INT( false, validateCommandDirection( &command, &game ) );
    command.direction = DIR_RIGHT;
    TEST_ASSERT_EQUAL_INT( true, validateCommandDirection( &command, &game ) );
}

// void testValidateCommandDropAmount( void )
// {
//     Command command = newCommand();
//     Game game = newGame( 5 );
//
//     command.fileX = FILE_A;
//     command.rankY = RANK_1;
//     command.drops = 1;
//     game.stackBuffer.stoneCount = 3;
//
//     command.dropCounts[0] = -1;
//     TEST_ASSERT_EQUAL_INT( false, validateCommandDropAmount( &command, &game ) );
//
//     command.dropCounts[0] = 0;
//     TEST_ASSERT_EQUAL_INT( true, validateCommandDropAmount( &command, &game ) );
//
//     command.dropCounts[0] = 3;
//     TEST_ASSERT_EQUAL_INT( true, validateCommandDropAmount( &command, &game ) );
//
//     command.dropCounts[0] = 4;
//     TEST_ASSERT_EQUAL_INT( true, validateCommandDropAmount( &command, &game ) );
//     TEST_ASSERT_EQUAL_INT( 3, command.dropCounts[0] );
// }

void testValidateCommand( void )
{
    Command command = newCommand( PLAYER_WHITE );
    Game game = newGame( 5 );

    TEST_ASSERT_EQUAL_INT( false, validateCommand( &command, &game ) );

    command.state = STATE_GET_ACTION_TYPE;
    command.playerId = PLAYER_WHITE;
    command.actionType = ACTION_TYPE_PLACE;
    TEST_ASSERT_EQUAL_INT( true, validateCommand( &command, &game ) );

    command.state = STATE_GET_STONE_TYPE;
    command.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( true, validateCommand( &command, &game ) );

    command.state = STATE_GET_FILE_X;
    command.fileX = FILE_A;
    TEST_ASSERT_EQUAL_INT( true, validateCommand( &command, &game ) );

    command.state = STATE_GET_RANK_Y;
    command.rankY = RANK_1;
    TEST_ASSERT_EQUAL_INT( true, validateCommand( &command, &game ) );

    command.state = STATE_GET_DIRECTION;
    command.actionType = ACTION_TYPE_LIFT;
    command.direction = DIR_UP;
    TEST_ASSERT_EQUAL_INT( true, validateCommand( &command, &game ) );

    command.state = STATE_GET_FIRST_DROP_AMOUNT;
    command.actionType = ACTION_TYPE_DROP;
    command.dropCounts[0] = 3;
    command.drops = 1;
    TEST_ASSERT_EQUAL_INT( true, validateCommand( &command, &game ) );

    command.state = STATE_GET_DROP_AMOUNT;
    TEST_ASSERT_EQUAL_INT( true, validateCommand( &command, &game ) );
}

#endif
