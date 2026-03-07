#ifndef IG20260104182515
#define IG20260104182515

#include "Board.h"
#include "BoardSystem.h"
#include "PlayerId.h"
#include "StoneType.h"
#include <unity.h>

void testNewBoard( void )
{
    Board board = newBoard( 3 );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, board.types[0] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, board.types[9 - 1] );
    TEST_ASSERT_EQUAL_INT( 0, board.counts[0] );
    TEST_ASSERT_EQUAL_INT( 0, board.counts[9 - 1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, board.stoneIds[( 3 * 3 * 20 ) - 1] );

    board = newBoard( 8 );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, board.types[0] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, board.types[( 8 * 8 ) - 1] );
    TEST_ASSERT_EQUAL_INT( 0, board.counts[0] );
    TEST_ASSERT_EQUAL_INT( 0, board.counts[( 8 * 8 ) - 1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, board.stoneIds[( 8 * 8 * 101 ) - 1] );
}

void testPlaceStoneOnBoard( void )
{
    Board board = newBoard( 5 );

    placeStoneOnBoard(
        &board,
        0,
        PLAYER_BLACK,
        STONE_TYPE_FLAT
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, board.types[0] );
    TEST_ASSERT_EQUAL_INT( 1, board.counts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stoneIds[0] );

    placeStoneOnBoard(
        &board,
        1,
        PLAYER_BLACK,
        STONE_TYPE_STANDING
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, board.types[1] );
    TEST_ASSERT_EQUAL_INT( 1, board.counts[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stoneIds[( ( 1 * 43 ) + 1 ) - 1] );

    placeStoneOnBoard(
        &board,
        3,
        PLAYER_WHITE,
        STONE_TYPE_CAP
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, board.types[3] );
    TEST_ASSERT_EQUAL_INT( 1, board.counts[3] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, board.stoneIds[( ( 3 * 43 ) + 1 ) - 1] );
}

void testPushOntoStack( void )
{
    Board board = newBoard( 5 );

    pushOntoStack(
        &board,
        0,
        PLAYER_WHITE
    );

    TEST_ASSERT_EQUAL_INT( 1, board.counts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, board.stoneIds[0] );

    pushOntoStack(
        &board,
        0,
        PLAYER_BLACK
    );

    TEST_ASSERT_EQUAL_INT( 2, board.counts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stoneIds[0 + 2 - 1] );

    pushOntoStack(
        &board,
        12,
        PLAYER_WHITE
    );

    TEST_ASSERT_EQUAL_INT( 1, board.counts[12] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, board.stoneIds[( 12 * 43 ) + 1 - 1] );

    pushOntoStack(
        &board,
        24,
        PLAYER_BLACK
    );

    TEST_ASSERT_EQUAL_INT( 1, board.counts[( 5 * 5 ) - 1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stoneIds[( ( 5 * 5 ) - 1 ) * 43] );
}

void testPopFromStack( void )
{
    Board board = newBoard( 5 );

    pushOntoStack(
        &board,
        12,
        PLAYER_WHITE
    );

    popFromStack(
        &board,
        12
    );

    TEST_ASSERT_EQUAL_INT( 0, board.counts[12] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, board.stoneIds[( 12 * 43 ) + 1 - 1] );
}

#endif
