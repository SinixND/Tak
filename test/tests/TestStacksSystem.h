#ifndef IG20260104182515
#define IG20260104182515

#include "Stacks.h"
#include "StoneType.h"
#include <unity.h>

void testInitStacks( void )
{
    //* EXECUTE
    Stacks stacks = newStacks( 5 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( (int)NONE, stacks.types[0] );
    TEST_ASSERT_EQUAL_INT( (int)NONE, stacks.types[25] );
    TEST_ASSERT_EQUAL_INT( 0, stacks.heights[0] );
    TEST_ASSERT_EQUAL_INT( 0, stacks.heights[25] );
    TEST_ASSERT_EQUAL_INT( 0, stacks.affiliations[0][0] );
    TEST_ASSERT_EQUAL_INT( 0, stacks.affiliations[25][43] );
}

void testPutStoneOnStack( void )
{
    //* SETUP
    Stacks stacks = newStacks( 5 );

    //* EXECUTE
    stacks = putStoneOnStack(
        stacks,
        0,
        1,
        FLAT
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( (int)FLAT, stacks.types[0] );
    TEST_ASSERT_EQUAL_INT( 1, stacks.heights[0] );
    TEST_ASSERT_EQUAL_INT( 1, stacks.affiliations[0][0] );

    //* EXECUTE
    stacks = putStoneOnStack(
        stacks,
        0,
        2,
        WALL
    );

    TEST_ASSERT_EQUAL_INT( (int)WALL, stacks.types[0] );
    TEST_ASSERT_EQUAL_INT( 2, stacks.heights[0] );
    TEST_ASSERT_EQUAL_INT( 2, stacks.affiliations[0][1] );

    //* EXECUTE
    stacks = putStoneOnStack(
        stacks,
        0,
        1,
        CAP
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( (int)CAP, stacks.types[0] );
    TEST_ASSERT_EQUAL_INT( 3, stacks.heights[0] );
    TEST_ASSERT_EQUAL_INT( 1, stacks.affiliations[0][2] );
}

#endif
