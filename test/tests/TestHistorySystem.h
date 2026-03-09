#ifndef IG20260309123925
#define IG20260309123925

#include "GameConstants.h"
#include "History.h"
#include "HistorySystem.h"
#include "PlayerAction.h"
#include "StoneType.h"
#include <unity.h>

void testRecordPlacementAction( void )
{
    History history = { 0 };

    recordPlacementAction(
        &history,
        STONE_TYPE_FLAT,
        0,
        0
    );

    PlayerAction action = history.undoActions[history.lastActionIdx];

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, action.stoneType );
    TEST_ASSERT_EQUAL_INT( 0, action.fileX );
    TEST_ASSERT_EQUAL_INT( 0, action.rankY );

    recordPlacementAction(
        &history,
        STONE_TYPE_STANDING,
        1,
        0
    );

    action = history.undoActions[history.lastActionIdx];

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, action.stoneType );
    TEST_ASSERT_EQUAL_INT( 1, action.fileX );
    TEST_ASSERT_EQUAL_INT( 0, action.rankY );

    recordPlacementAction(
        &history,
        STONE_TYPE_CAP,
        2,
        0
    );

    action = history.undoActions[history.lastActionIdx];

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, action.stoneType );
    TEST_ASSERT_EQUAL_INT( 2, action.fileX );
    TEST_ASSERT_EQUAL_INT( 0, action.rankY );
}

void testStepBack( void )
{
    History history = { 0 };

    stepBack( &history );

    TEST_ASSERT_EQUAL_INT( HISTORY_SIZE - 1, history.lastActionIdx );
}

void testStepForward( void )
{
    History history = { 0 };

    stepBack( &history );
    stepForward( &history );

    TEST_ASSERT_EQUAL_INT( 0, history.lastActionIdx );
}

#endif
