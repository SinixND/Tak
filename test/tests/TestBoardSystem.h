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
    TEST_ASSERT_EQUAL_INT( 0, board.stacks[0].height );
    TEST_ASSERT_EQUAL_INT( 0, board.stacks[25].height );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, board.stacks[0].affiliations[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, board.stacks[25].affiliations[43] );
}

void testPutStoneOnStack( void )
{
    //* SETUP
    Board board = newBoard();

    //* EXECUTE
    board = putStoneOnStack(
        board,
        0,
        PLAYER_BLACK,
        STONE_TYPE_FLAT
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, board.types[0] );
    TEST_ASSERT_EQUAL_INT( 1, board.stacks[0].height );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stacks[0].affiliations[0] );

    //* EXECUTE
    board = putStoneOnStack(
        board,
        0,
        PLAYER_BLACK,
        STONE_TYPE_WALL
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_WALL, board.types[0] );
    TEST_ASSERT_EQUAL_INT( 2, board.stacks[0].height );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, board.stacks[0].affiliations[1] );

    //* EXECUTE
    board = putStoneOnStack(
        board,
        0,
        PLAYER_WHITE,
        STONE_TYPE_CAP
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, board.types[0] );
    TEST_ASSERT_EQUAL_INT( 3, board.stacks[0].height );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, board.stacks[0].affiliations[2] );
}

#endif
