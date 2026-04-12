#ifndef IG20260408232415
#define IG20260408232415

#include "ActionTypeId.h"
#include "Command.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <unity.h>

void testNewCommand( void )
{
    Command command = newCommand();

    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, command.playerId );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, command.actionType );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, command.stoneType );
    TEST_ASSERT_EQUAL_INT( FILE_NONE, command.fileX );
    TEST_ASSERT_EQUAL_INT( RANK_NONE, command.rankY );
    TEST_ASSERT_EQUAL_INT( DIR_NONE, command.direction );
    TEST_ASSERT_EQUAL_INT( -1, command.drops );
    TEST_ASSERT_EQUAL_INT( -1, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( -1, command.dropCounts[7] );
}

void testIsCommandComplete( void )
{
    Command command = newCommand();

    TEST_ASSERT_EQUAL_INT( false, isCommandComplete( &command ) );

    command.actionType = ACTION_TYPE_PLACE;

    TEST_ASSERT_EQUAL_INT( false, isCommandComplete( &command ) );

    command.fileX = FILE_B;
    command.rankY = RANK_2;
    command.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( false, isCommandComplete( &command ) );

    command.playerId = PLAYER_WHITE;
    TEST_ASSERT_EQUAL_INT( true, isCommandComplete( &command ) );

    command.actionType = ACTION_TYPE_LIFT;
    command.fileX = FILE_NONE;
    TEST_ASSERT_EQUAL_INT( false, isCommandComplete( &command ) );

    command.fileX = FILE_B;
    TEST_ASSERT_EQUAL_INT( true, isCommandComplete( &command ) );

    command.actionType = ACTION_TYPE_DROP;
    TEST_ASSERT_EQUAL_INT( false, isCommandComplete( &command ) );

    command.direction = DIR_DOWN;
    command.drops = 0;
    TEST_ASSERT_EQUAL_INT( false, isCommandComplete( &command ) );

    command.dropCounts[0] = 1;
    TEST_ASSERT_EQUAL_INT( true, isCommandComplete( &command ) );
}

#endif
