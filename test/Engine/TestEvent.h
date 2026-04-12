#ifndef IG20260406173020
#define IG20260406173020

#include "ActionTypeId.h"
#include "Event.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <unity.h>

void testNewEvent( void )
{
    Event event = newEvent();

    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, event.playerId );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, event.actionType );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, event.stoneType );
    TEST_ASSERT_EQUAL_INT( -1, event.squareIdx );
    TEST_ASSERT_EQUAL_INT( -1, event.dropCount );
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
