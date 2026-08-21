#ifndef IG20260415183932
#define IG20260415183932

#include "ActionTypeId.h"
#include "Command.h"
#include "CommandId.h"
#include "CommandStateId.h"
#include "DirectionId.h"
#include "FileId.h"
#include "Game.h"
#include "InputBuffer.h"
#include "InputParsing.h"
#include "Mappings.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <unity.h>

void testParseInputActionType( void )
{
    Command command = newCommand( PLAYER_WHITE );
    InputBuffer inputBuffer = newInputBuffer();

    TEST_ASSERT_EQUAL_INT( false, parseInputActionType( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, command.actionType );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_ACTION_TYPE][COMMAND_PLACE];
    TEST_ASSERT_EQUAL_INT( true, parseInputActionType( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_PLACE, command.actionType );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_ACTION_TYPE][COMMAND_MOVE];
    TEST_ASSERT_EQUAL_INT( true, parseInputActionType( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_LIFT, command.actionType );
}

void testParseInputStoneType( void )
{
    Command command = newCommand( PLAYER_WHITE );
    InputBuffer inputBuffer = newInputBuffer();

    TEST_ASSERT_EQUAL_INT( false, parseInputStoneType( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, command.stoneType );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_STONE_TYPE][COMMAND_FLAT];
    TEST_ASSERT_EQUAL_INT( true, parseInputStoneType( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, command.stoneType );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_STONE_TYPE][COMMAND_STANDING];
    TEST_ASSERT_EQUAL_INT( true, parseInputStoneType( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, command.stoneType );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_STONE_TYPE][COMMAND_CAPSTONE];
    TEST_ASSERT_EQUAL_INT( true, parseInputStoneType( &command, &inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, command.stoneType );
}

void testParseInputFileX( void )
{
    Command command = newCommand( PLAYER_WHITE );
    InputBuffer inputBuffer = newInputBuffer();

    TEST_ASSERT_EQUAL_INT( false, parseInputPosition( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( FILE_NONE, command.fileX );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_A];
    TEST_ASSERT_EQUAL_INT( true, parseInputPosition( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( FILE_A, command.fileX );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_B];
    TEST_ASSERT_EQUAL_INT( true, parseInputPosition( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( FILE_B, command.fileX );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_C];
    TEST_ASSERT_EQUAL_INT( true, parseInputPosition( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( FILE_C, command.fileX );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_D];
    TEST_ASSERT_EQUAL_INT( true, parseInputPosition( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( FILE_D, command.fileX );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_E];
    TEST_ASSERT_EQUAL_INT( true, parseInputPosition( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( FILE_E, command.fileX );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_F];
    TEST_ASSERT_EQUAL_INT( true, parseInputPosition( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( FILE_F, command.fileX );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_G];
    TEST_ASSERT_EQUAL_INT( true, parseInputPosition( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( FILE_G, command.fileX );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_H];
    TEST_ASSERT_EQUAL_INT( true, parseInputPosition( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( FILE_H, command.fileX );
}

void testParseInputRankY( void )
{
    Command command = newCommand( PLAYER_WHITE );
    InputBuffer inputBuffer = newInputBuffer();
    Game game = newGame( 8 );

    command.fileX = FILE_A;
    game.board.stackIds[0] = PLAYER_WHITE;

    TEST_ASSERT_EQUAL_INT( false, parseInputRankY( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( RANK_NONE, command.rankY );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_1];
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( RANK_1, command.rankY );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, command.actionType );

    command.actionType = ACTION_TYPE_NONE;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_2];
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( RANK_2, command.rankY );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, command.actionType );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_3];
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( RANK_3, command.rankY );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_4];
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( RANK_4, command.rankY );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_5];
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( RANK_5, command.rankY );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_6];
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( RANK_6, command.rankY );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_7];
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( RANK_7, command.rankY );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_8];
    TEST_ASSERT_EQUAL_INT( true, parseInputRankY( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( RANK_8, command.rankY );
}

void testParseInputDirection( void )
{
    Command command = newCommand( PLAYER_WHITE );
    InputBuffer inputBuffer = newInputBuffer();
    int const boardSize = 8;

    TEST_ASSERT_EQUAL_INT( false, parseInputDirection( &command, &inputBuffer, boardSize ) );
    TEST_ASSERT_EQUAL_INT( DIR_NONE, command.direction );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_DIRECTION][COMMAND_UP];
    TEST_ASSERT_EQUAL_INT( true, parseInputDirection( &command, &inputBuffer, boardSize ) );
    TEST_ASSERT_EQUAL_INT( DIR_UP, command.direction );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_DIRECTION][COMMAND_DOWN];
    TEST_ASSERT_EQUAL_INT( true, parseInputDirection( &command, &inputBuffer, boardSize ) );
    TEST_ASSERT_EQUAL_INT( DIR_DOWN, command.direction );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_DIRECTION][COMMAND_LEFT];
    TEST_ASSERT_EQUAL_INT( true, parseInputDirection( &command, &inputBuffer, boardSize ) );
    TEST_ASSERT_EQUAL_INT( DIR_LEFT, command.direction );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_DIRECTION][COMMAND_RIGHT];
    TEST_ASSERT_EQUAL_INT( true, parseInputDirection( &command, &inputBuffer, boardSize ) );
    TEST_ASSERT_EQUAL_INT( DIR_RIGHT, command.direction );
}

void testParseInputFirstDropAmount( void )
{
    Command command = newCommand( PLAYER_WHITE );
    InputBuffer inputBuffer = newInputBuffer();

    TEST_ASSERT_EQUAL_INT( false, parseInputFirstDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( -1, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( 0, command.drops );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_0];
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 0, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_1];
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 1, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_2];
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 2, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_3];
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 3, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_4];
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 4, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_5];
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 5, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_6];
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 6, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_7];
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 7, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.drops = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_8];
    TEST_ASSERT_EQUAL_INT( true, parseInputFirstDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 8, command.dropCounts[0] );
}

void testParseInputDropAmount( void )
{
    Command command = newCommand( PLAYER_WHITE );
    InputBuffer inputBuffer = newInputBuffer();

    command.drops = 1;
    TEST_ASSERT_EQUAL_INT( false, parseInputDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( -1, command.dropCounts[command.drops] );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_1];
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 1, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_2];
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 2, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_3];
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 3, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_4];
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 4, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_5];
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 5, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_6];
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 6, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_7];
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 7, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_8];
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 8, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.drops = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_ALL];
    TEST_ASSERT_EQUAL_INT( true, parseInputDropAmount( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 8, command.dropCounts[1] );
}

void testParseInput( void )
{
    Command command = newCommand( PLAYER_WHITE );
    InputBuffer inputBuffer = newInputBuffer();
    Game game = newGame( 5 );

    command.state = COMMAND_STATE_DEFAULT;
    TEST_ASSERT_EQUAL_INT( false, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_INPUT_FIRST][COMMAND_FLAT];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_INPUT_FIRST][COMMAND_A];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );

    command.state = COMMAND_STATE_GET_ACTION_TYPE;
    TEST_ASSERT_EQUAL_INT( false, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_ACTION_TYPE][COMMAND_MOVE];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );

    command.state = COMMAND_STATE_GET_STONE_TYPE;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_STONE_TYPE][COMMAND_STANDING];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );

    command.state = COMMAND_STATE_GET_POSITION;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_A];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );

    command.state = COMMAND_STATE_GET_RANK_Y;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_POSITION][COMMAND_1];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );

    command.state = COMMAND_STATE_GET_DIRECTION;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_DIRECTION][COMMAND_RIGHT];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );

    command.state = COMMAND_STATE_GET_FIRST_DROP_AMOUNT;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_0];
    command.drops = 0;
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );

    command.state = COMMAND_STATE_GET_DROP_AMOUNT;
    command.drops = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_1];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );
}

#endif
