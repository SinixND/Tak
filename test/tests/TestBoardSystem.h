#ifndef IG20260104182515
#define IG20260104182515

#include "Board.h"
#include "BoardSystem.h"
#include "StoneType.h"
#include <unity.h>

void testNewStacks( void )
{
    //* EXECUTE
    Board board = newBoard();

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( (int)NONE, board.types[0] );
    TEST_ASSERT_EQUAL_INT( (int)NONE, board.types[25] );
    TEST_ASSERT_EQUAL_INT( 0, board.heights[0] );
    TEST_ASSERT_EQUAL_INT( 0, board.heights[25] );
    TEST_ASSERT_EQUAL_INT( 0, board.stacks[0][0] );
    TEST_ASSERT_EQUAL_INT( 0, board.stacks[25][43] );
}

void testPutStoneOnStack( void )
{
    //* SETUP
    Board board = newBoard();

    //* EXECUTE
    board = putStoneOnStack(
        board,
        0,
        1,
        FLAT
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( (int)FLAT, board.types[0] );
    TEST_ASSERT_EQUAL_INT( 1, board.heights[0] );
    TEST_ASSERT_EQUAL_INT( 1, board.stacks[0][0] );

    //* EXECUTE
    board = putStoneOnStack(
        board,
        0,
        2,
        WALL
    );

    TEST_ASSERT_EQUAL_INT( (int)WALL, board.types[0] );
    TEST_ASSERT_EQUAL_INT( 2, board.heights[0] );
    TEST_ASSERT_EQUAL_INT( 2, board.stacks[0][1] );

    //* EXECUTE
    board = putStoneOnStack(
        board,
        0,
        1,
        CAP
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( (int)CAP, board.types[0] );
    TEST_ASSERT_EQUAL_INT( 3, board.heights[0] );
    TEST_ASSERT_EQUAL_INT( 1, board.stacks[0][2] );
}

#endif
