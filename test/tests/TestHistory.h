#ifndef IG20260309123925
#define IG20260309123925

#include "History.h"
#include "HistoryRecord.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <unity.h>

void testRecordPlacementAction( void )
{
    History history = { 0 };

    recordActionPlacement(
        &history,
        PLAYER_WHITE,
        0,
        STONE_TYPE_FLAT
    );

    TEST_ASSERT_EQUAL_INT( 1, history.lastRecordIdx );

    HistoryRecord action = history.records[history.lastRecordIdx];

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, action.playerId );
    TEST_ASSERT_EQUAL_INT( 0, action.squareIdx );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, action.stoneType );

    recordActionPlacement(
        &history,
        PLAYER_WHITE,
        1,
        STONE_TYPE_STANDING
    );

    TEST_ASSERT_EQUAL_INT( 2, history.lastRecordIdx );

    action = history.records[history.lastRecordIdx];

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, action.playerId );
    TEST_ASSERT_EQUAL_INT( 1, action.squareIdx );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, action.stoneType );

    recordActionPlacement(
        &history,
        PLAYER_WHITE,
        2,
        STONE_TYPE_CAP
    );

    TEST_ASSERT_EQUAL_INT( 3, history.lastRecordIdx );

    action = history.records[history.lastRecordIdx];

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, action.playerId );
    TEST_ASSERT_EQUAL_INT( 2, action.squareIdx );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, action.stoneType );
}

void testRecordLiftAction( void )
{
    History history = { 0 };

    recordLiftAction(
        &history,
        PLAYER_WHITE,
        STONE_TYPE_STANDING,
        5
    );

    TEST_ASSERT_EQUAL_INT( 1, history.lastRecordIdx );

    HistoryRecord action = history.records[history.lastRecordIdx];

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, action.playerId );
    TEST_ASSERT_EQUAL_INT( 0, action.squareIdx );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, action.stoneType );
    TEST_ASSERT_EQUAL_INT( 5, action.stoneCount );
}

void testRecordDropAction( void )
{
    History history = { 0 };

    recordDropAction(
        &history,
        PLAYER_WHITE,
        0,
        STONE_TYPE_FLAT,
        true
    );

    TEST_ASSERT_EQUAL_INT( 1, history.lastRecordIdx );

    HistoryRecord action = history.records[history.lastRecordIdx];

    TEST_ASSERT_EQUAL_INT( 0, action.squareIdx );
    TEST_ASSERT_EQUAL_INT( 1, action.stoneCount );
    TEST_ASSERT_EQUAL_INT( true, action.flattened );
}

void testUndoHistory( void )
{
    History history = { 0 };

    recordActionPlacement(
        &history,
        PLAYER_WHITE,
        2,
        STONE_TYPE_STANDING
    );

    recordActionPlacement(
        &history,
        PLAYER_WHITE,
        1,
        STONE_TYPE_CAP
    );

    undoHistory( &history );

    TEST_ASSERT_EQUAL_INT( 1, history.lastRecordIdx );
    TEST_ASSERT_EQUAL_INT( 1, history.redoCount );

    undoHistory( &history );

    TEST_ASSERT_EQUAL_INT( 0, history.lastRecordIdx );
    TEST_ASSERT_EQUAL_INT( 2, history.redoCount );

    recordActionPlacement(
        &history,
        PLAYER_WHITE,
        2,
        STONE_TYPE_FLAT
    );

    TEST_ASSERT_EQUAL_INT( 1, history.lastRecordIdx );
    TEST_ASSERT_EQUAL_INT( 0, history.redoCount );
}

void testRedoHistory( void )
{
    History history = { 0 };

    recordActionPlacement(
        &history,
        PLAYER_WHITE,
        2,
        STONE_TYPE_CAP
    );

    undoHistory( &history );
    redoHistory( &history );

    TEST_ASSERT_EQUAL_INT( 1, history.lastRecordIdx );
    TEST_ASSERT_EQUAL_INT( 0, history.redoCount );
}

#endif
