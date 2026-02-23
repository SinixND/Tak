#ifndef IG20260104182445
#define IG20260104182445

#include "Players.h"
#include "PlayersSystem.h"
#include <unity.h>

void testNewPlayers( void )
{
    //* EXECUTE
    Players players = newPlayers( 3 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 0, players.stonesInPlay[0] );
    TEST_ASSERT_EQUAL_INT( 0, players.stonesInPlay[1] );
    TEST_ASSERT_EQUAL_INT( 0, players.stonesInPlay[2] );
    TEST_ASSERT_EQUAL_INT( 0, players.regularReserves[0] );
    TEST_ASSERT_EQUAL_INT( 10, players.regularReserves[1] );
    TEST_ASSERT_EQUAL_INT( 10, players.regularReserves[2] );
    TEST_ASSERT_EQUAL_INT( 0, players.capstoneReserves[0] );
    TEST_ASSERT_EQUAL_INT( 0, players.capstoneReserves[1] );
    TEST_ASSERT_EQUAL_INT( 0, players.capstoneReserves[2] );
}

void testTakeFromReserves( void )
{
    //* SETUP
    Players players = newPlayers( 5 );

    //* Execute
    players = takeFromReserves(
        players,
        1,
        FLAT
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        0,
        players.regularReserves[0]
    );

    TEST_ASSERT_EQUAL_INT(
        20,
        players.regularReserves[1]
    );

    TEST_ASSERT_EQUAL_INT(
        21,
        players.regularReserves[2]
    );

    //* Execute
    players = takeFromReserves(
        players,
        2,
        CAP
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        0,
        players.capstoneReserves[0]
    );

    TEST_ASSERT_EQUAL_INT(
        1,
        players.capstoneReserves[1]
    );

    TEST_ASSERT_EQUAL_INT(
        0,
        players.capstoneReserves[2]
    );
}

#endif
