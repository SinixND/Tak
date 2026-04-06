#ifndef IG20260406173020
#define IG20260406173020

#include "ActionTypeId.h"
#include "Event.h"
#include "FileId.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <unity.h>

void testNewEvent( void )
{
    Event event = newEvent();

    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, event.playerId );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, event.actionType );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, event.stoneType );
    TEST_ASSERT_EQUAL_INT( FILE_NONE, event.fileX );
    TEST_ASSERT_EQUAL_INT( RANK_NONE, event.rankY );
    TEST_ASSERT_EQUAL_INT( -1, event.dropCount );
}

#endif
