#ifndef IG20260408232415
#define IG20260408232415

#include "ActionTypeId.h"
#include "Command.h"
#include "CommandStateId.h"
#include "InputBuffer.h"
#include "InputId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <unity.h>

void testNewCommand( void )
{
    Command command = newCommand();

    TEST_ASSERT_EQUAL_INT( STATE_GET_ACTION, command.state );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, command.playerId );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, command.actionType );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, command.stoneType );
    TEST_ASSERT_EQUAL_INT( FILE_NONE, command.fileX );
    TEST_ASSERT_EQUAL_INT( RANK_NONE, command.rankY );
    TEST_ASSERT_EQUAL_INT( DIR_NONE, command.direction );
    TEST_ASSERT_EQUAL_INT( -1, command.drops );
    TEST_ASSERT_EQUAL_INT( -1, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( -1, command.dropCounts[7] );
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

void testParseInputAction( void )
{
    Command command = newCommand();
    InputBuffer inputBuffer = newInputBuffer();

    TEST_ASSERT_EQUAL_INT( false, parseInputAction( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, command.actionType );

    inputBuffer.keyboard = INPUT_P;
    TEST_ASSERT_EQUAL_INT( true, parseInputAction( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_PLACE, command.actionType );

    inputBuffer.keyboard = INPUT_M;
    TEST_ASSERT_EQUAL_INT( true, parseInputAction( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_LIFT, command.actionType );
}

void testParseInputStoneType( void )
{
    Command command = newCommand();
    InputBuffer inputBuffer = newInputBuffer();

    TEST_ASSERT_EQUAL_INT( false, parseInputStoneType( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, command.stoneType );

    inputBuffer.keyboard = INPUT_F;
    TEST_ASSERT_EQUAL_INT( true, parseInputStoneType( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, command.stoneType );

    inputBuffer.keyboard = INPUT_S;
    TEST_ASSERT_EQUAL_INT( true, parseInputStoneType( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, command.stoneType );

    inputBuffer.keyboard = INPUT_C;
    TEST_ASSERT_EQUAL_INT( true, parseInputStoneType( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, command.stoneType );
}

void testHandleStateGetAction( void )
{
    Command command = newCommand();
    InputBuffer inputBuffer = newInputBuffer();

    TEST_ASSERT_EQUAL_INT( STATE_GET_ACTION, command.state );

    handleStateGetAction( &command, &inputBuffer );
    TEST_ASSERT_EQUAL_INT( STATE_GET_ACTION, command.state );

    inputBuffer.keyboard = INPUT_P;
    handleStateGetAction( &command, &inputBuffer );
    TEST_ASSERT_EQUAL_INT( STATE_GET_STONE_TYPE, command.state );

    command.state = STATE_GET_ACTION;
    inputBuffer.keyboard = INPUT_M;
    handleStateGetAction( &command, &inputBuffer );
    TEST_ASSERT_EQUAL_INT( STATE_GET_FILE_X, command.state );
}

void testHandleStateGetStoneType( void )
{
    Command command = newCommand();
    InputBuffer inputBuffer = newInputBuffer();

    command.state = STATE_GET_STONE_TYPE;
    handleStateGetStoneType( &command, &inputBuffer );
    TEST_ASSERT_EQUAL_INT( STATE_GET_STONE_TYPE, command.state );

    inputBuffer.keyboard = INPUT_F;
    handleStateGetStoneType( &command, &inputBuffer );
    TEST_ASSERT_EQUAL_INT( STATE_GET_FILE_X, command.state );

    command.state = STATE_GET_STONE_TYPE;
    inputBuffer.keyboard = INPUT_S;
    handleStateGetStoneType( &command, &inputBuffer );
    TEST_ASSERT_EQUAL_INT( STATE_GET_FILE_X, command.state );

    command.state = STATE_GET_STONE_TYPE;
    inputBuffer.keyboard = INPUT_C;
    handleStateGetStoneType( &command, &inputBuffer );
    TEST_ASSERT_EQUAL_INT( STATE_GET_FILE_X, command.state );
}

#endif
