#include "Stacks.h"
#include "StacksSystem.h"
#include "StoneType.h"
#include "unity.h"

void testPutStoneOnStack( void )
{
    //* SETUP
    int const boardWidth = 3;

    Stacks stacks = newStacks( boardWidth );

    StoneType type = FLAT;

    //* EXECUTE
    stacks = putStoneOnStack(
        stacks,
        0,
        1,
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
