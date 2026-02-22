#ifndef IG20260104182445
#define IG20260104182445

#include "Players.h"
#include <unity.h>

void testInitPlayers( void )
{
    //* SETUP
    int const playerCount = 2;
    int const regularReserves = 1;
    int const capstoneReserves = 1;

    //* EXECUTE
    Players players = initPlayers(
        playerCount,
        regularReserves,
        capstoneReserves
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( playerCount, players.count );
    TEST_ASSERT_EQUAL_INT( regularReserves, players.capstoneReserves[0] );
    TEST_ASSERT_EQUAL_INT( regularReserves, players.capstoneReserves[1] );
    TEST_ASSERT_EQUAL_INT( capstoneReserves, players.capstoneReserves[0] );
    TEST_ASSERT_EQUAL_INT( capstoneReserves, players.capstoneReserves[1] );

    //* CLEANUP
    deinitPlayers( &players );
}

#endif
