#ifndef IG20260104182515
#define IG20260104182515

#include "Board.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <unity.h>

void testPutOntoStack( void )
{
    Board board = newBoard( 5 );

    putOntoStack(
        &board,
        PLAYER_BLACK,
        6,
        STONE_TYPE_FLAT
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, board.stackTypes[6] );
    TEST_ASSERT_EQUAL_INT( 1, board.stoneCounts[6] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stoneIds[6 * getStackCapacity( 5 )] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stackIds[6] );

    putOntoStack(
        &board,
        PLAYER_BLACK,
        3,
        STONE_TYPE_STANDING
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, board.stackTypes[3] );
    TEST_ASSERT_EQUAL_INT( 1, board.stoneCounts[3] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stoneIds[3 * getStackCapacity( 5 )] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stackIds[3] );

    putOntoStack(
        &board,
        PLAYER_WHITE,
        3,
        STONE_TYPE_CAP
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, board.stackTypes[3] );
    TEST_ASSERT_EQUAL_INT( 2, board.stoneCounts[3] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, board.stoneIds[3 * getStackCapacity( 5 ) + 1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, board.stackIds[3] );
}

void testTakeFromStack( void )
{
    Board board = newBoard( 5 );

    board.stoneCounts[0] = 2;
    board.stackTypes[0] = STONE_TYPE_STANDING;
    board.stackIds[0] = PLAYER_WHITE;
    board.stoneIds[0] = PLAYER_BLACK;
    board.stoneIds[1] = PLAYER_WHITE;

    takeFromStack(
        &board,
        0,
        1
    );

    TEST_ASSERT_EQUAL_INT( 1, board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stackIds[0] );

    takeFromStack(
        &board,
        0,
        1
    );

    TEST_ASSERT_EQUAL_INT( 0, board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, board.stackIds[0] );
}

#endif
