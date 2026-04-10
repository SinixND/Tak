#ifndef IG20260410171141
#define IG20260410171141

#include "Engine.h"
#include <unity.h>

void testNewEngine( void )
{
    Engine engine = newEngine();

    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, engine.event.playerId );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, engine.event.actionType );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, engine.event.stoneType );
    TEST_ASSERT_EQUAL_INT( -1, engine.event.squareIdx );
    TEST_ASSERT_EQUAL_INT( -1, engine.event.dropCount );

    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, engine.command.playerId );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, engine.command.actionType );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, engine.command.stoneType );
    TEST_ASSERT_EQUAL_INT( FILE_NONE, engine.command.fileX );
    TEST_ASSERT_EQUAL_INT( RANK_NONE, engine.command.rankY );
    TEST_ASSERT_EQUAL_INT( DIR_NONE, engine.command.direction );
    TEST_ASSERT_EQUAL_INT( -1, engine.command.drops );
    TEST_ASSERT_EQUAL_INT( -1, engine.command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( -1, engine.command.dropCounts[7] );
}

#endif
