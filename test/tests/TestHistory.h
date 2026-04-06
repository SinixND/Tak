#ifndef IG20260309123925
#define IG20260309123925

#include "History.h"
#include "HistoryRecord.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <unity.h>

void testRecordActionPlacement( void )
{
    History history = { 0 };

    recordActionPlacement(
        &history,
        PLAYER_WHITE,
        0,
        STONE_TYPE_FLAT
    );

    TEST_ASSERT_EQUAL_INT( 1, history.lastRecordIdx );

    HistoryRecord record = history.records[history.lastRecordIdx];

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, record.playerId );
    TEST_ASSERT_EQUAL_INT( 0, record.squareIdx );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, record.stoneType );

    recordActionPlacement(
        &history,
        PLAYER_WHITE,
        1,
        STONE_TYPE_STANDING
    );

    TEST_ASSERT_EQUAL_INT( 2, history.lastRecordIdx );

    record = history.records[history.lastRecordIdx];

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, record.playerId );
    TEST_ASSERT_EQUAL_INT( 1, record.squareIdx );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, record.stoneType );

    recordActionPlacement(
        &history,
        PLAYER_WHITE,
        2,
        STONE_TYPE_CAP
    );

    TEST_ASSERT_EQUAL_INT( 3, history.lastRecordIdx );

    record = history.records[history.lastRecordIdx];

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, record.playerId );
    TEST_ASSERT_EQUAL_INT( 2, record.squareIdx );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, record.stoneType );
}

void testRecordActionLift( void )
{
    History history = { 0 };

    recordActionLift(
        &history,
        0
    );

    TEST_ASSERT_EQUAL_INT( 1, history.lastRecordIdx );

    HistoryRecord record = history.records[history.lastRecordIdx];

    TEST_ASSERT_EQUAL_INT( 0, record.squareIdx );
}

void testRecordActionDrop( void )
{
    History history = { 0 };

    recordActionDrop(
        &history,
        0,
        true
    );

    TEST_ASSERT_EQUAL_INT( 1, history.lastRecordIdx );

    HistoryRecord record = history.records[history.lastRecordIdx];

    TEST_ASSERT_EQUAL_INT( 0, record.squareIdx );
    TEST_ASSERT_EQUAL_INT( true, record.flattened );
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
