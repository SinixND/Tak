#ifndef IG20260104182445
#define IG20260104182445

#include "PlayerId.h"
#include "Players.h"
#include "PlayersSystem.h"
#include <unity.h>

void testNewPlayers( void )
{
    Players players = newPlayers( 3 );

    TEST_ASSERT_EQUAL_INT( 10, players.reservesRegular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 10, players.reservesRegular[PLAYER_BLACK] );
    TEST_ASSERT_EQUAL_INT( 0, players.reservesCapstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, players.reservesCapstone[PLAYER_BLACK] );
}

void testTakeFromReserves( void )
{
    Players players = newPlayers( 5 );

    takeFromReserves(
        &players,
        PLAYER_WHITE,
        STONE_TYPE_FLAT
    );

    TEST_ASSERT_EQUAL_INT( 20, players.reservesRegular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 21, players.reservesRegular[PLAYER_BLACK] );

    takeFromReserves(
        &players,
        PLAYER_BLACK,
        STONE_TYPE_CAP
    );

    TEST_ASSERT_EQUAL_INT( 1, players.reservesCapstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, players.reservesCapstone[PLAYER_BLACK] );
}

#endif
