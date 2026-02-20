#include "Players.h"
#include "ReserveSystem.h"
#include "StoneType.h"
#include "Stones.h"
#include "unity.h"

void testTakeFromReserves( void )
{
    //* SETUP
    int const playerCount = 1;
    int const regularReserves = 2;
    int const capstoneReserves = 1;

    int const player = 0;

    Players players = initPlayers(
        playerCount,
        regularReserves,
        capstoneReserves
    );

    Stones stones = initStones(
        playerCount,
        regularReserves
            + capstoneReserves
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        0,
        takeFromReserves(
            players.regularReserves,
            players.capstoneReserves,
            &stones.inPlayCount,
            player,
            FLAT
        )
    );

    TEST_ASSERT_EQUAL_INT(
        1,
        takeFromReserves(
            players.regularReserves,
            players.capstoneReserves,
            &stones.inPlayCount,
            player,
            WALL
        )
    );

    TEST_ASSERT_EQUAL_INT(
        2,
        takeFromReserves(
            players.regularReserves,
            players.capstoneReserves,
            &stones.inPlayCount,
            player,
            CAP
        )
    );

    TEST_ASSERT_EQUAL_INT( 0, players.regularReserves[0] );
    TEST_ASSERT_EQUAL_INT( 0, players.capstoneReserves[0] );

    //* CLEANUP
    deinitPlayers( &players );
    deinitStones( &stones );
}
