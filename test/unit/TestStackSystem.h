#include "Board.h"
#include "GameConstants.h"
#include "StackSystem.h"
#include "Stacks.h"
#include "StoneType.h"
#include "Stones.h"
#include "unity.h"

void testCreateOrGetStackIdx( void )
{
    //* SETUP
    int const boardWith = 1;

    Board board = initBoard( boardWith );
    Stacks stacks = initStacks( boardWith );

    int stackIdx = board.stackIdxs[0];

    //* VERIFY
    //* Precondition: Index invalid
    TEST_ASSERT_EQUAL_INT( -1, stackIdx );

    //* First run: New valid index created
    stackIdx = createOrGetStackIdx(
        board.stackIdxs,
        &stacks.onBoardCount,
        stacks.boardIdxs,
        0
    );
    TEST_ASSERT_EQUAL_INT( 0, stackIdx );

    //* Second run on same tile: Same index returned
    stackIdx = createOrGetStackIdx(
        board.stackIdxs,
        &stacks.onBoardCount,
        stacks.boardIdxs,
        0
    );
    TEST_ASSERT_EQUAL_INT( 0, stackIdx );

    //* CLEANUP
    deinitBoard( &board );
    deinitStacks( &stacks );
}
