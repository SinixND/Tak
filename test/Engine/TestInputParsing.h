#ifndef IG20260415183932
#define IG20260415183932

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

void testParseInput( void )
{
    Command command = newCommand();
    InputBuffer inputBuffer = newInputBuffer();

    command.state = STATE_GET_ACTION_TYPE;
    TEST_ASSERT_EQUAL_INT( false, parseInput( &command, &inputBuffer ) );

    inputBuffer.keyboard = INPUT_P;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );

    inputBuffer.keyboard = INPUT_M;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );

    command.state = STATE_GET_STONE_TYPE;
    inputBuffer.keyboard = INPUT_F;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_S;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_C;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );

    command.state = STATE_GET_FILE_X;
    inputBuffer.keyboard = INPUT_A;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_B;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_C;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_D;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_E;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_F;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_G;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_H;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );

    command.state = STATE_GET_RANK_Y;
    inputBuffer.keyboard = INPUT_1;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_2;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_3;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_4;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_5;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_6;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_7;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_8;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );

    command.state = STATE_GET_DIRECTION;
    inputBuffer.keyboard = INPUT_E;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_N;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_S;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    inputBuffer.keyboard = INPUT_W;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );

    command.state = STATE_GET_FIRST_DROP_AMOUNT;
    inputBuffer.keyboard = INPUT_0;
    command.drops = 0;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 0;
    inputBuffer.keyboard = INPUT_1;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 0;
    inputBuffer.keyboard = INPUT_2;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 0;
    inputBuffer.keyboard = INPUT_3;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 0;
    inputBuffer.keyboard = INPUT_4;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 0;
    inputBuffer.keyboard = INPUT_5;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 0;
    inputBuffer.keyboard = INPUT_6;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 0;
    inputBuffer.keyboard = INPUT_7;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 0;
    inputBuffer.keyboard = INPUT_8;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );

    command.state = STATE_GET_DROP_AMOUNT;
    command.drops = 1;
    inputBuffer.keyboard = INPUT_1;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 1;
    inputBuffer.keyboard = INPUT_2;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 1;
    inputBuffer.keyboard = INPUT_3;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 1;
    inputBuffer.keyboard = INPUT_4;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 1;
    inputBuffer.keyboard = INPUT_5;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 1;
    inputBuffer.keyboard = INPUT_6;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 1;
    inputBuffer.keyboard = INPUT_7;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
    command.drops = 1;
    inputBuffer.keyboard = INPUT_8;
    TEST_ASSERT_EQUAL_INT( true, parseInput( &command, &inputBuffer ) );
}

#endif
