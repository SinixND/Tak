#ifndef IG20260408232415
#define IG20260408232415

#include "ActionTypeId.h"
#include "Command.h"
#include "CommandStateId.h"
#include "DirectionId.h"
#include "FileId.h"
#include "InputBuffer.h"
#include "InputId.h"
#include "InputParsing.h"
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
    TEST_ASSERT_EQUAL_INT( 0, command.drops );
    TEST_ASSERT_EQUAL_INT( -1, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( -1, command.dropCounts[7] );
}

void testParseInputActionType( void )
{
    Command command = newCommand();
    InputBuffer inputBuffer = newInputBuffer();

    TEST_ASSERT_EQUAL_INT( false, parseInputActionType( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, command.actionType );

    inputBuffer.keyboard = INPUT_P;
    TEST_ASSERT_EQUAL_INT( true, parseInputActionType( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_PLACE, command.actionType );

    inputBuffer.keyboard = INPUT_M;
    TEST_ASSERT_EQUAL_INT( true, parseInputActionType( &command, &inputBuffer ) );
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

void testParseInputFileX( void )
{
    Command command = newCommand();
    InputBuffer inputBuffer = newInputBuffer();

    TEST_ASSERT_EQUAL_INT( false, parseInputFileX( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( FILE_NONE, command.fileX );

    inputBuffer.keyboard = INPUT_A;
    TEST_ASSERT_EQUAL_INT( true, parseInputFileX( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( FILE_A, command.fileX );

    inputBuffer.keyboard = INPUT_B;
    TEST_ASSERT_EQUAL_INT( true, parseInputFileX( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( FILE_B, command.fileX );

    inputBuffer.keyboard = INPUT_C;
    TEST_ASSERT_EQUAL_INT( true, parseInputFileX( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( FILE_C, command.fileX );

    inputBuffer.keyboard = INPUT_D;
    TEST_ASSERT_EQUAL_INT( true, parseInputFileX( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( FILE_D, command.fileX );

    inputBuffer.keyboard = INPUT_E;
    TEST_ASSERT_EQUAL_INT( true, parseInputFileX( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( FILE_E, command.fileX );

    inputBuffer.keyboard = INPUT_F;
    TEST_ASSERT_EQUAL_INT( true, parseInputFileX( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( FILE_F, command.fileX );

    inputBuffer.keyboard = INPUT_G;
    TEST_ASSERT_EQUAL_INT( true, parseInputFileX( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( FILE_G, command.fileX );

    inputBuffer.keyboard = INPUT_H;
    TEST_ASSERT_EQUAL_INT( true, parseInputFileX( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( FILE_H, command.fileX );
}

void testParseInputRankY( void )
{
    Command command = newCommand();
    InputBuffer inputBuffer = newInputBuffer();

    TEST_ASSERT_EQUAL_INT( false, parseInputRankY( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( RANK_NONE, command.rankY );

    inputBuffer.keyboard = INPUT_1;
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( RANK_1, command.rankY );

    inputBuffer.keyboard = INPUT_2;
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( RANK_2, command.rankY );

    inputBuffer.keyboard = INPUT_3;
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( RANK_3, command.rankY );

    inputBuffer.keyboard = INPUT_4;
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( RANK_4, command.rankY );

    inputBuffer.keyboard = INPUT_5;
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( RANK_5, command.rankY );

    inputBuffer.keyboard = INPUT_6;
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( RANK_6, command.rankY );

    inputBuffer.keyboard = INPUT_7;
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( RANK_7, command.rankY );

    inputBuffer.keyboard = INPUT_8;
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( RANK_8, command.rankY );
}

void testParseInputDirection( void )
{
    Command command = newCommand();
    InputBuffer inputBuffer = newInputBuffer();

    TEST_ASSERT_EQUAL_INT( false, parseInputDirection( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( DIR_NONE, command.direction );

    inputBuffer.keyboard = INPUT_E;
    TEST_ASSERT_EQUAL_INT( true, parseInputDirection( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( DIR_RIGHT, command.direction );

    inputBuffer.keyboard = INPUT_N;
    TEST_ASSERT_EQUAL_INT( true, parseInputDirection( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( DIR_UP, command.direction );

    inputBuffer.keyboard = INPUT_S;
    TEST_ASSERT_EQUAL_INT( true, parseInputDirection( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( DIR_DOWN, command.direction );

    inputBuffer.keyboard = INPUT_W;
    TEST_ASSERT_EQUAL_INT( true, parseInputDirection( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( DIR_LEFT, command.direction );
}

void testParseInputFirstDropAmount( void )
{
    Command command = newCommand();
    InputBuffer inputBuffer = newInputBuffer();

    TEST_ASSERT_EQUAL_INT( false, parseInputFirstDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( -1, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( 0, command.drops );

    inputBuffer.keyboard = INPUT_0;
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 0, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( 1, command.drops );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.keyboard = INPUT_1;
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 1, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( 1, command.drops );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.keyboard = INPUT_2;
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 2, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( 1, command.drops );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.keyboard = INPUT_3;
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 3, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( 1, command.drops );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.keyboard = INPUT_4;
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 4, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( 1, command.drops );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.keyboard = INPUT_5;
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 5, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( 1, command.drops );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.keyboard = INPUT_6;
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 6, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( 1, command.drops );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.keyboard = INPUT_7;
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 7, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( 1, command.drops );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.keyboard = INPUT_8;
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 8, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( 1, command.drops );
}

void testParseInputDropAmount( void )
{
    Command command = newCommand();
    InputBuffer inputBuffer = newInputBuffer();

    command.drops = 1;
    TEST_ASSERT_EQUAL_INT( false, parseInputDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( -1, command.dropCounts[command.drops] );
    TEST_ASSERT_EQUAL_INT( 1, command.drops );

    inputBuffer.keyboard = INPUT_1;
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 1, command.dropCounts[1] );
    TEST_ASSERT_EQUAL_INT( 2, command.drops );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.keyboard = INPUT_2;
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 2, command.dropCounts[1] );
    TEST_ASSERT_EQUAL_INT( 2, command.drops );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.keyboard = INPUT_3;
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 3, command.dropCounts[1] );
    TEST_ASSERT_EQUAL_INT( 2, command.drops );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.keyboard = INPUT_4;
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 4, command.dropCounts[1] );
    TEST_ASSERT_EQUAL_INT( 2, command.drops );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.keyboard = INPUT_5;
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 5, command.dropCounts[1] );
    TEST_ASSERT_EQUAL_INT( 2, command.drops );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.keyboard = INPUT_6;
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 6, command.dropCounts[1] );
    TEST_ASSERT_EQUAL_INT( 2, command.drops );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.keyboard = INPUT_7;
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 7, command.dropCounts[1] );
    TEST_ASSERT_EQUAL_INT( 2, command.drops );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.keyboard = INPUT_8;
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 8, command.dropCounts[1] );
    TEST_ASSERT_EQUAL_INT( 2, command.drops );
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
