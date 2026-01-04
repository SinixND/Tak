#ifndef IG20260104182515
#define IG20260104182515

#include "Stacks.h"
#include "StoneType.h"
#include <unity.h>

void testInitStacks( void )
{
    //* SETUP
    int const boardWidth = 1;

    //* EXECUTE
    Stacks stacks = initStacks( boardWidth );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 0, stacks.onBoardCount );
    TEST_ASSERT_EQUAL_INT( -1, stacks.topStoneIdxs[0] );
    TEST_ASSERT_EQUAL_INT( 0, stacks.heights[0] );
    TEST_ASSERT_EQUAL_INT( NONE, stacks.types[0] );

    //* CLEANUP
    deinitStacks( &stacks );
}

#endif
