#ifndef IG20260410112002
#define IG20260410112002

#include "ActionTypeId.h"
#include "Event.h"
#include "EventExecution.h"
#include "Game.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <unity.h>

void testExecuteEvent( void )
{
    Event event = newEvent();
    Game game = newGame( 0 );

    event.actionType = ACTION_TYPE_PLACE;
    event.playerId = PLAYER_WHITE;
    event.squareIdx = 0;
    event.stoneType = STONE_TYPE_STANDING;

    executeEvent( &game, &event );

    TEST_ASSERT_EQUAL_INT( 20, game.reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.stackTypes[0] );

    event.actionType = ACTION_TYPE_LIFT;

    executeEvent( &game, &event );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.stackBuffer.stoneType );
    TEST_ASSERT_EQUAL_INT( 1, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.stackBuffer.stoneIds[0] );

    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[0] );

    event.actionType = ACTION_TYPE_DROP;
    event.dropCount = 1;

    executeEvent( &game, &event );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
}

#endif
