#ifndef IG20260415174842
#define IG20260415174842

#include "ActionTypeId.h"
#include "Command.h"
#include "CommandStateId.h"
#include "Engine.h"
#include "Event.h"
#include "Game.h"
#include "InputBuffer.h"
#include <unity.h>

void testAutocompleteCommand( void )
{
}

void testBuildCommand( void )
{
    Command command = newCommand();
    InputBuffer inputBuffer = newInputBuffer();
    Game game = newGame( 5 );

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
    Command command = newCommand();
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
