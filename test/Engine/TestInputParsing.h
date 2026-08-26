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

void testParseInputDirection( void )
{
    Command command = newCommand( PLAYER_WHITE );
    InputBuffer inputBuffer = newInputBuffer();
    int const boardSize = 8;

    TEST_ASSERT_EQUAL_INT( false, parseDirectionInputToCommand( &command, &inputBuffer, boardSize ) );
    TEST_ASSERT_EQUAL_INT( DIR_NONE, command.direction );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_DIRECTION][COMMAND_UP];
    TEST_ASSERT_EQUAL_INT( true, parseDirectionInputToCommand( &command, &inputBuffer, boardSize ) );
    TEST_ASSERT_EQUAL_INT( DIR_UP, command.direction );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_DIRECTION][COMMAND_DOWN];
    TEST_ASSERT_EQUAL_INT( true, parseDirectionInputToCommand( &command, &inputBuffer, boardSize ) );
    TEST_ASSERT_EQUAL_INT( DIR_DOWN, command.direction );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_DIRECTION][COMMAND_LEFT];
    TEST_ASSERT_EQUAL_INT( true, parseDirectionInputToCommand( &command, &inputBuffer, boardSize ) );
    TEST_ASSERT_EQUAL_INT( DIR_LEFT, command.direction );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_DIRECTION][COMMAND_RIGHT];
    TEST_ASSERT_EQUAL_INT( true, parseDirectionInputToCommand( &command, &inputBuffer, boardSize ) );
    TEST_ASSERT_EQUAL_INT( DIR_RIGHT, command.direction );
}

void testParseInputFirstDropAmount( void )
{
    Command command = newCommand( PLAYER_WHITE );
    InputBuffer inputBuffer = newInputBuffer();

    TEST_ASSERT_EQUAL_INT( false, parseFirstDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( -1, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( 0, command.currentDropIdx );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_0];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 0, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_1];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 1, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_2];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 2, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_3];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 3, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_4];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 4, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_5];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 5, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_6];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 6, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_7];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 7, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_8];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 8, command.dropCounts[0] );
}

void testParseInputDropAmount( void )
{
    Command command = newCommand( PLAYER_WHITE );
    InputBuffer inputBuffer = newInputBuffer();

    command.currentDropIdx = 1;
    TEST_ASSERT_EQUAL_INT( false, parseDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( -1, command.dropCounts[command.currentDropIdx] );

    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_1];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 1, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_2];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 2, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_3];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 3, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_4];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 4, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_5];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 5, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_6];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 6, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_7];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 7, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_8];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 8, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_ALL];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &inputBuffer, 8 ) );
    TEST_ASSERT_EQUAL_INT( 8, command.dropCounts[1] );
}

void testParseInput( void )
{
    Command command = newCommand( PLAYER_WHITE );
    InputBuffer inputBuffer = newInputBuffer();
    Game game = newGame( 5 );

    command.state = COMMAND_STATE_DEFAULT;
    TEST_ASSERT_EQUAL_INT( false, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_INPUT_DEFAULT][COMMAND_FLAT];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_INPUT_DEFAULT][COMMAND_A];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_INPUT_DEFAULT][COMMAND_H];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_INPUT_DEFAULT][COMMAND_E];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );

    command.state = COMMAND_STATE_GET_DIRECTION;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_DIRECTION][COMMAND_RIGHT];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );

    command.state = COMMAND_STATE_GET_FIRST_DROP_AMOUNT;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_0];
    command.currentDropIdx = 0;
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );

    command.state = COMMAND_STATE_GET_DROP_AMOUNT;
    command.currentDropIdx = 1;
    inputBuffer.lastInput = inputBuffer.mappings.inputs[CONTEXT_AMOUNT][COMMAND_1];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &inputBuffer, game.board.size ) );
}

#endif
