#ifndef IG20260104182139
#define IG20260104182139

#include "Board.h"
#include "unity.h"

void testInitBoard( void )
{
    //* SETUP
    int const boardWidth = 2;

    //* EXECUTE
    Board board = initBoard( boardWidth );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( ( boardWidth * boardWidth ), board.tileCount );
    TEST_ASSERT_EQUAL_INT( -1, board.stackIdxs[0] );

    //* CLEANUP
    deinitBoard( &board );
}

#endif
