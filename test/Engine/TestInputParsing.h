#ifndef IG20260415183932
#define IG20260415183932

#include "Command.h"
#include "CommandId.h"
#include "CommandStateId.h"
#include "DirectionId.h"
#include "Game.h"
#include "Input.h"
#include "InputParsing.h"
#include "Mappings.h"
#include "PlayerId.h"
#include "UI.h"
#include <unity.h>

void testParseInputDirection( void )
{
    Command command = newCommand( PLAYER_WHITE );
    Input input = newInput();
    UI ui = newUI();
    int const boardSize = 8;

    TEST_ASSERT_EQUAL_INT( false, parseDirectionInputToCommand( &command, &input, boardSize, &ui ) );
    TEST_ASSERT_EQUAL_INT( DIR_NONE, command.direction );

    input.lastInput = input.mappings.inputs[CONTEXT_DIRECTION][COMMAND_UP];
    TEST_ASSERT_EQUAL_INT( true, parseDirectionInputToCommand( &command, &input, boardSize, &ui ) );
    TEST_ASSERT_EQUAL_INT( DIR_UP, command.direction );

    input.lastInput = input.mappings.inputs[CONTEXT_DIRECTION][COMMAND_DOWN];
    TEST_ASSERT_EQUAL_INT( true, parseDirectionInputToCommand( &command, &input, boardSize, &ui ) );
    TEST_ASSERT_EQUAL_INT( DIR_DOWN, command.direction );

    input.lastInput = input.mappings.inputs[CONTEXT_DIRECTION][COMMAND_LEFT];
    TEST_ASSERT_EQUAL_INT( true, parseDirectionInputToCommand( &command, &input, boardSize, &ui ) );
    TEST_ASSERT_EQUAL_INT( DIR_LEFT, command.direction );

    input.lastInput = input.mappings.inputs[CONTEXT_DIRECTION][COMMAND_RIGHT];
    TEST_ASSERT_EQUAL_INT( true, parseDirectionInputToCommand( &command, &input, boardSize, &ui ) );
    TEST_ASSERT_EQUAL_INT( DIR_RIGHT, command.direction );
}

void testParseInputFirstDropAmount( void )
{
    Command command = newCommand( PLAYER_WHITE );
    Input input = newInput();
    UI ui = newUI();

    TEST_ASSERT_EQUAL_INT( false, parseFirstDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( -1, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( 0, command.currentDropIdx );

    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_0];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 0, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_1];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 1, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_2];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 2, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_3];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 3, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_4];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 4, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_5];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 5, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_6];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 6, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_7];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 7, command.dropCounts[0] );

    command.dropCounts[0] = -1;
    command.currentDropIdx = 0;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_8];
    TEST_ASSERT_EQUAL_INT( true, parseFirstDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 8, command.dropCounts[0] );
}

void testParseInputDropAmount( void )
{
    Command command = newCommand( PLAYER_WHITE );
    Input input = newInput();
    UI ui = newUI();

    command.currentDropIdx = 1;
    TEST_ASSERT_EQUAL_INT( false, parseDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( -1, command.dropCounts[command.currentDropIdx] );

    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_1];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 1, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_2];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 2, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_3];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 3, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_4];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 4, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_5];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 5, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_6];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 6, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_7];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 7, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_8];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 8, command.dropCounts[1] );

    command.dropCounts[1] = -1;
    command.currentDropIdx = 1;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_ALL];
    TEST_ASSERT_EQUAL_INT( true, parseDropAmountInputToCommand( &command, &input, 8, &ui ) );
    TEST_ASSERT_EQUAL_INT( 8, command.dropCounts[1] );
}

void testParseInput( void )
{
    Command command = newCommand( PLAYER_WHITE );
    Input input = newInput();
    Game game = newGame( 5 );
    UI ui = newUI();

    command.state = COMMAND_STATE_DEFAULT;
    TEST_ASSERT_EQUAL_INT( false, updateCommandFromInput( &command, &input, game.board.size, &ui ) );
    input.lastInput = input.mappings.inputs[CONTEXT_INPUT_DEFAULT][COMMAND_FLAT];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &input, game.board.size, &ui ) );
    input.lastInput = input.mappings.inputs[CONTEXT_INPUT_DEFAULT][COMMAND_A];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &input, game.board.size, &ui ) );
    input.lastInput = input.mappings.inputs[CONTEXT_INPUT_DEFAULT][COMMAND_H];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &input, game.board.size, &ui ) );
    input.lastInput = input.mappings.inputs[CONTEXT_INPUT_DEFAULT][COMMAND_E];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &input, game.board.size, &ui ) );

    command.state = COMMAND_STATE_GET_DIRECTION;
    input.lastInput = input.mappings.inputs[CONTEXT_DIRECTION][COMMAND_RIGHT];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &input, game.board.size, &ui ) );

    command.state = COMMAND_STATE_GET_FIRST_DROP_AMOUNT;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_0];
    command.currentDropIdx = 0;
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &input, game.board.size, &ui ) );

    command.state = COMMAND_STATE_GET_DROP_AMOUNT;
    command.currentDropIdx = 1;
    input.lastInput = input.mappings.inputs[CONTEXT_AMOUNT][COMMAND_1];
    TEST_ASSERT_EQUAL_INT( true, updateCommandFromInput( &command, &input, game.board.size, &ui ) );
}

#endif
