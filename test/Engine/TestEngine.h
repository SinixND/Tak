#ifndef IG20260415174842
#define IG20260415174842

#include "ActionTypeId.h"
#include "Command.h"
#include "CommandStateId.h"
#include "DirectionId.h"
#include "Engine.h"
#include "Event.h"
#include "FileId.h"
#include "Game.h"
#include "InputBuffer.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <unity.h>

void testAutocompleteCommand( void )
{
    Command command = newCommand( PLAYER_WHITE );
    Game game = newGame( 3 );

    command.fileX = FILE_A;
    command.rankY = RANK_1;
    command.direction = DIR_RIGHT;

    /// Need to drop 'all' if only one stone left in stack buffer and not first drop
    command.state = STATE_GET_DROP_AMOUNT;
    game.stackBuffer.stoneCount = 1; // Only one stone left in stack
    command.drops = 1;               // Not first drop
    autocompleteCommand(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( 1, command.dropCounts[1] );

    /// Need to drop all if next squares type is capstone
    game.stackBuffer.stoneCount = 2;
    command.state = STATE_GET_FIRST_DROP_AMOUNT;
    command.drops = 0;                         // Next square index is 0
    game.board.stackTypes[1] = STONE_TYPE_CAP; // Next squares type is capstone
    autocompleteCommand(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( 2, command.dropCounts[0] );

    /// Need to drop all if next squares type is standing and buffer type is not capstone
    game.stackBuffer.stoneCount = 2;
    command.state = STATE_GET_FIRST_DROP_AMOUNT;
    command.drops = 0;                              // Next square index is 0
    game.board.stackTypes[1] = STONE_TYPE_STANDING; // Next squares type is standing
    game.stackBuffer.stackType = STONE_TYPE_FLAT;   // Buffertype is not capstone
    autocompleteCommand(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( 2, command.dropCounts[0] );

    /// Need to drop all but one if next squares type is standing and buffer type is capstone
    game.stackBuffer.stoneCount = 2;
    command.state = STATE_GET_FIRST_DROP_AMOUNT;
    command.drops = 0;                              // Next square index is 0
    game.board.stackTypes[1] = STONE_TYPE_STANDING; // Next squares type is standing
    game.stackBuffer.stackType = STONE_TYPE_CAP;    // Buffertype is capstone
    autocompleteCommand(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( 1, command.dropCounts[0] );

    /// Need to drop all if next square out of board
    command.state = STATE_GET_DROP_AMOUNT;
    command.drops = 2; // Next square index is out of board
    command.dropCounts[0] = 0;
    command.dropCounts[1] = 1;
    game.stackBuffer.stoneCount = 2; // Two stones left in stack after previous drops
    autocompleteCommand(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( 2, command.dropCounts[2] );
}

void testBuildCommand( void )
{
    Command command = newCommand( PLAYER_WHITE );
    InputBuffer inputBuffer = newInputBuffer();
    Game game = newGame( 5 );

    command.fileX = FILE_A;
    command.rankY = RANK_1;
    command.state = STATE_GET_DROP_AMOUNT;
    command.actionType = ACTION_TYPE_DROP;
    command.drops = 1;
    command.dropCounts[0] = 2;
    game.stackBuffer.stoneCount = 3;
    inputBuffer.keyboard = INPUT_4;

    buildCommand(
        &command,
        &inputBuffer,
        &game
    );

    TEST_ASSERT_EQUAL_INT( 3, command.dropCounts[1] );
}

void testBuildEvent( void )
{
    Event event = newEvent();
    Command command = newCommand( PLAYER_WHITE );
    int const boardSize = 5;

    command.playerId = PLAYER_WHITE;
    command.actionType = ACTION_TYPE_PLACE;
    command.stoneType = STONE_TYPE_STANDING;
    command.fileX = FILE_B;
    command.rankY = RANK_2;
    command.direction = DIR_DOWN;
    command.dropCounts[0] = 0;
    command.dropCounts[1] = 2;
    command.drops = 2;

    buildEvent(
        &event,
        &command,
        boardSize
    );

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, event.playerId );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_PLACE, event.actionType );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, event.stoneType );
    TEST_ASSERT_EQUAL_INT( 6, event.squareIdx );
    TEST_ASSERT_EQUAL_INT( 2, event.dropCount );
}

#endif
