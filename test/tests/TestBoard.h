#ifndef IG20260104182515
#define IG20260104182515

#include "Board.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <unity.h>

void testNewBoard( void )
{
    Board board = newBoard( 3 );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, board.stackTypes[9 - 1] );
    TEST_ASSERT_EQUAL_INT( 0, board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( 0, board.stoneCounts[9 - 1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, board.stoneIds[( 3 * 3 * 20 ) - 1] );

    board = newBoard( 8 );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, board.stackTypes[( 8 * 8 ) - 1] );
    TEST_ASSERT_EQUAL_INT( 0, board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( 0, board.stoneCounts[( 8 * 8 ) - 1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, board.stoneIds[( 8 * 8 * 101 ) - 1] );
}

void testPlaceOntoStack( void )
{
    Board board = newBoard( 5 );

    putOntoStack(
        &board,
        PLAYER_BLACK,
        0,
        STONE_TYPE_FLAT
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( 1, board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stoneIds[0] );

    putOntoStack(
        &board,
        PLAYER_BLACK,
        3,
        STONE_TYPE_STANDING
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, board.stackTypes[3] );
    TEST_ASSERT_EQUAL_INT( 1, board.stoneCounts[3] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stoneIds[( ( 3 * 43 ) + 1 ) - 1] );

    putOntoStack(
        &board,
        PLAYER_WHITE,
        3,
        STONE_TYPE_CAP
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, board.stackTypes[3] );
    TEST_ASSERT_EQUAL_INT( 2, board.stoneCounts[3] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, board.stoneIds[( ( 3 * 43 ) + 2 ) - 1] );
}

void testTakeFromStack( void )
{
    Board board = newBoard( 5 );

    board.stoneCounts[0] = 3;

    takeFromStack(
        &board,
        0,
        1
    );

    TEST_ASSERT_EQUAL_INT( 2, board.stoneCounts[0] );
}

#endif
