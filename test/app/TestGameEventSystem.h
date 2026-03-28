#ifndef IG20260327200417
#define IG20260327200417

#include "GameEvent.h"
#include "GameEventSystem.h"
#include "GameSystem.h"
#include <unity.h>

void testNewGameEvent( void )
{
    GameEvent event = newGameEvent();

    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, event.stoneId );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, event.actionType );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, event.stoneType );
    TEST_ASSERT_EQUAL_INT( FILE_NONE, event.fileX );
    TEST_ASSERT_EQUAL_INT( RANK_NONE, event.rankY );
    TEST_ASSERT_EQUAL_INT( DIR_NONE, event.direction );
    TEST_ASSERT_EQUAL_INT( 0, event.liftCount );
    TEST_ASSERT_EQUAL_INT( -1, event.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( -1, event.dropCounts[BOARD_WIDTH_MAX - 1] );
    TEST_ASSERT_EQUAL_INT( 0, event.dropCountsSize );
    TEST_ASSERT_EQUAL_INT( 0, event.droppedCount );
}

void testIsStoneTypeAvailable( void )
{
    GameEvent event = newGameEvent();
}

void testIsFileXOnBoard( void )
{
    GameEvent event = newGameEvent();
}

void testIsRankYOnBoard( void )
{
    GameEvent event = newGameEvent();
}

void testIsSquareEmpty( void )
{
    GameEvent event = newGameEvent();
}

void testDoesPlayerOwnStack( void )
{
    GameEvent event = newGameEvent();
}

void testIsCaptiveValid( void )
{
    GameEvent event = newGameEvent();
}

void testIsOffsetXOnBoard( void )
{
    GameEvent event = newGameEvent();
}

void testIsOffsetYOnBoard( void )
{
    GameEvent event = newGameEvent();
}

void testValidateEventPlace( void )
{
    GameEvent event = newGameEvent();
    Game game = newGame( 0 );
}

void testValidateEventLift( void )
{
    GameEvent event = newGameEvent();
    Game game = newGame( 0 );
}

void testValidateEventDrop( void )
{
    GameEvent event = newGameEvent();
    Game game = newGame( 0 );
}

#endif
