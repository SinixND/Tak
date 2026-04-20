#ifndef IG20260408232415
#define IG20260408232415

#include "ActionTypeId.h"
#include "Command.h"
#include "CommandStateId.h"
#include "DirectionId.h"
#include "FileId.h"
#include "Game.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <unity.h>

void testSetNextCommandState( void )
{
    Command command = newCommand();
    Game game = newGame( 3 );

    command.state = STATE_GET_ACTION_TYPE;
    command.actionType = ACTION_TYPE_PLACE;
    setNextCommandState(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( STATE_GET_STONE_TYPE, command.state );

    setNextCommandState(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( STATE_GET_FILE_X, command.state );

    setNextCommandState(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( STATE_GET_RANK_Y, command.state );

    setNextCommandState(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( STATE_GET_ACTION_TYPE, command.state );

    command.actionType = ACTION_TYPE_LIFT;
    setNextCommandState(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( STATE_GET_FILE_X, command.state );

    setNextCommandState(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( STATE_GET_RANK_Y, command.state );

    setNextCommandState(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( STATE_GET_DIRECTION, command.state );

    setNextCommandState(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( STATE_GET_FIRST_DROP_AMOUNT, command.state );

    setNextCommandState(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( STATE_GET_DROP_AMOUNT, command.state );

    command.drops = 2;
    command.dropCounts[0] = 1;
    command.dropCounts[1] = 2;
    game.stackBuffer.stoneCount = 2;
    setNextCommandState(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( STATE_GET_ACTION_TYPE, command.state );
}

void testIsCommandComplete( void )
{
    Command command = newCommand();

    TEST_ASSERT_EQUAL_INT( false, isCommandComplete( &command ) );

    command.actionType = ACTION_TYPE_PLACE;

    TEST_ASSERT_EQUAL_INT( false, isCommandComplete( &command ) );

    command.fileX = FILE_B;
    command.rankY = RANK_2;
    command.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( false, isCommandComplete( &command ) );

    command.playerId = PLAYER_WHITE;
    TEST_ASSERT_EQUAL_INT( true, isCommandComplete( &command ) );

    command.actionType = ACTION_TYPE_LIFT;
    command.fileX = FILE_NONE;
    TEST_ASSERT_EQUAL_INT( false, isCommandComplete( &command ) );

    command.fileX = FILE_B;
    TEST_ASSERT_EQUAL_INT( true, isCommandComplete( &command ) );

    command.actionType = ACTION_TYPE_DROP;
    TEST_ASSERT_EQUAL_INT( false, isCommandComplete( &command ) );

    command.direction = DIR_DOWN;
    command.drops = 0;
    TEST_ASSERT_EQUAL_INT( false, isCommandComplete( &command ) );

    command.dropCounts[0] = 1;
    TEST_ASSERT_EQUAL_INT( true, isCommandComplete( &command ) );
}

#endif
