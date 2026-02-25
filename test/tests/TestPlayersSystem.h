#ifndef IG20260104182445
#define IG20260104182445

#include "PlayerId.h"
#include "Players.h"
#include "PlayersSystem.h"
#include <unity.h>

void testNewPlayers( void )
{
    //* EXECUTE
    Players players = newPlayers( 3 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 0, players.stonesInPlay[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, players.stonesInPlay[PLAYER_BLACK] );
    TEST_ASSERT_EQUAL_INT( 10, players.regularReserves[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 10, players.regularReserves[PLAYER_BLACK] );
    TEST_ASSERT_EQUAL_INT( 0, players.capstoneReserves[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, players.capstoneReserves[PLAYER_BLACK] );
}

void testTakeFromReserves( void )
{
    //* SETUP
    Players players = newPlayers( 5 );

    //* Execute
    players = takeFromReserves(
        players,
        PLAYER_WHITE,
        STONE_TYPE_FLAT
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        20,
        players.regularReserves[PLAYER_WHITE]
    );

    TEST_ASSERT_EQUAL_INT(
        21,
        players.regularReserves[PLAYER_BLACK]
    );

    //* Execute
    players = takeFromReserves(
        players,
        PLAYER_BLACK,
        STONE_TYPE_CAP
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        1,
        players.capstoneReserves[PLAYER_WHITE]
    );

    TEST_ASSERT_EQUAL_INT(
        0,
        players.capstoneReserves[PLAYER_BLACK]
    );
}

#endif
