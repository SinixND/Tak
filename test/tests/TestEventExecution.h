#ifndef IG20260410112002
#define IG20260410112002

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

#endif
