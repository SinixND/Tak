#ifndef IG20260104182515
#define IG20260104182515

#include "Board.h"
#include "BoardSystem.h"
#include "PlayerId.h"
#include "StoneType.h"
#include <unity.h>

void testNewBoard( void )
{
    //* EXECUTE
    Board board = newBoard();

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, board.types[0] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, board.types[25] );
    TEST_ASSERT_EQUAL_INT( 0, board.stacks[0].count );
    TEST_ASSERT_EQUAL_INT( 0, board.stacks[25].count );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, board.stacks[0].stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, board.stacks[25].stoneIds[43] );
}

void testPlaceStoneOnBoard( void )
{
    //* SETUP
    Board board = newBoard();

    //* EXECUTE
    board = placeStoneOnBoard(
        board,
        0,
        PLAYER_BLACK,
        STONE_TYPE_FLAT
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, board.types[0] );
    TEST_ASSERT_EQUAL_INT( 1, board.stacks[0].count );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stacks[0].stoneIds[0] );

    //* EXECUTE
    board = placeStoneOnBoard(
        board,
        1,
        PLAYER_BLACK,
        STONE_TYPE_STANDING
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, board.types[1] );
    TEST_ASSERT_EQUAL_INT( 1, board.stacks[1].count );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stacks[1].stoneIds[0] );

    //* EXECUTE
    board = placeStoneOnBoard(
        board,
        3,
        PLAYER_WHITE,
        STONE_TYPE_CAP
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, board.types[3] );
    TEST_ASSERT_EQUAL_INT( 1, board.stacks[3].count );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, board.stacks[3].stoneIds[0] );
}

#endif
