#ifndef IG20260104182706
#define IG20260104182706

#include "Stones.h"
#include <unity.h>

void testInitStones( void )
{
    //* SETUP
    int const playerCount = 2;
    int const stoneCountPerPlayer = 1;

    //* EXECUTE
    Stones stones = initStones(
        playerCount,
        stoneCountPerPlayer
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 0, stones.inPlayCount );
    TEST_ASSERT_EQUAL_INT( -1, stones.playerIdxs[0] );
    TEST_ASSERT_EQUAL_INT( -1, stones.playerIdxs[1] );
    TEST_ASSERT_EQUAL_INT( -1, stones.captiveIdxs[0] );
    TEST_ASSERT_EQUAL_INT( -1, stones.captiveIdxs[1] );

    //* CLEANUP
    deinitStones( &stones );
}

#endif
