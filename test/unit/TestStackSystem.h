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

void testPutStoneOnStack( void )
{
    //* SETUP
    int const totalPlayerReserves = 1;
    int const boardWith = 1;

    Stones stones = initStones(
        PLAYER_COUNT,
        totalPlayerReserves
    );

    Stacks stacks = initStacks( boardWith );

    int oldStoneIdx = -1;
    int newStoneIdx = 0;
    int stackIdx = 0;
    StoneType type = FLAT;

    //* EXECUTE
    putStoneOnStack(
        &stones,
        &stacks,
        newStoneIdx,
        stackIdx,
        type
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( oldStoneIdx, stones.captiveIdxs[newStoneIdx] );
    TEST_ASSERT_EQUAL_INT( newStoneIdx, stacks.topStoneIdxs[stackIdx] );
    TEST_ASSERT_EQUAL_INT( type, stacks.types[stackIdx] );
    TEST_ASSERT_EQUAL_INT( 1, stacks.heights[stackIdx] );

    oldStoneIdx = newStoneIdx;
    newStoneIdx = 1;
    type = WALL;

    //* EXECUTE
    putStoneOnStack(
        &stones,
        &stacks,
        newStoneIdx,
        stackIdx,
        type
    );

    TEST_ASSERT_EQUAL_INT( oldStoneIdx, stones.captiveIdxs[newStoneIdx] );
    TEST_ASSERT_EQUAL_INT( newStoneIdx, stacks.topStoneIdxs[stackIdx] );
    TEST_ASSERT_EQUAL_INT( type, stacks.types[stackIdx] );
    TEST_ASSERT_EQUAL_INT( 2, stacks.heights[stackIdx] );

    oldStoneIdx = newStoneIdx;
    newStoneIdx = 1;
    type = CAP;

    //* EXECUTE
    putStoneOnStack(
        &stones,
        &stacks,
        newStoneIdx,
        stackIdx,
        type
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( oldStoneIdx, stones.captiveIdxs[newStoneIdx] );
    TEST_ASSERT_EQUAL_INT( newStoneIdx, stacks.topStoneIdxs[stackIdx] );
    TEST_ASSERT_EQUAL_INT( type, stacks.types[stackIdx] );
    TEST_ASSERT_EQUAL_INT( 3, stacks.heights[stackIdx] );

    //* CLEANUP
    deinitStones( &stones );
    deinitStacks( &stacks );
}
