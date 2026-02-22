#include "PlayerSystem.h"
#include "Players.h"
#include "StoneType.h"
#include "unity.h"

void testTakeFromReserves( void )
{
    //* SETUP
    int const boardWidth = 3;
    int const playerIdx = 1;

    Players players = newPlayers( boardWidth );

    //* Execute
    takeFromReserves(
        players,
        playerIdx,
        FLAT
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        1,
        players.regularReserves[playerIdx]
    );

    //* Execute
    takeFromReserves(
        players,
        playerIdx,
        CAP
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        1,
        players.capstoneReserves[playerIdx]
    );

    TEST_ASSERT_EQUAL_INT( 0, players.regularReserves[0] );
    TEST_ASSERT_EQUAL_INT( 0, players.capstoneReserves[0] );
}
