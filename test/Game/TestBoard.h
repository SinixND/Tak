#ifndef IG20260104182515
#define IG20260104182515

#include "Board.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <unity.h>

void testPlaceOntoStack( void )
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

    putOntoStack(
        &board,
        PLAYER_BLACK,
        3,
        STONE_TYPE_STANDING
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, board.stackTypes[3] );
    TEST_ASSERT_EQUAL_INT( 1, board.stoneCounts[3] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stoneIds[3 * getStackCapacity( 5 )] );

    putOntoStack(
        &board,
        PLAYER_WHITE,
        3,
        STONE_TYPE_CAP
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, board.stackTypes[3] );
    TEST_ASSERT_EQUAL_INT( 2, board.stoneCounts[3] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, board.stoneIds[3 * getStackCapacity( 5 ) + 1] );
}

void testTakeFromStack( void )
{
    Board board = newBoard( 5 );

    board.stoneCounts[6] = 3;

    takeFromStack(
        &board,
        6,
        1
    );

    TEST_ASSERT_EQUAL_INT( 2, board.stoneCounts[6] );
}

#endif
