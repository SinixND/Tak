#ifndef IG20260104182445
#define IG20260104182445

#include "GameConstants.h"
#include "PlayerId.h"
#include "Reserves.h"
#include <unity.h>

void testNewReserves( void )
{
    Reserves reserves = newReserves( 3 );

    TEST_ASSERT_EQUAL_INT( getReservesRegular( 3 ), reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( getReservesRegular( 3 ), reserves.regular[PLAYER_BLACK] );
    TEST_ASSERT_EQUAL_INT( getReservesCapstone( 3 ), reserves.capstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( getReservesCapstone( 3 ), reserves.capstone[PLAYER_BLACK] );
}

void testTakeFromReserves( void )
{
    Reserves reserves = newReserves( 5 );

    takeFromReserves(
        &reserves,
        PLAYER_WHITE,
        STONE_TYPE_FLAT
    );

    TEST_ASSERT_EQUAL_INT( getReservesRegular( 5 ) - 1, reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( getReservesRegular( 5 ), reserves.regular[PLAYER_BLACK] );

    takeFromReserves(
        &reserves,
        PLAYER_BLACK,
        STONE_TYPE_CAP
    );

    TEST_ASSERT_EQUAL_INT( getReservesCapstone( 5 ), reserves.capstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( getReservesCapstone( 5 ) - 1, reserves.capstone[PLAYER_BLACK] );
}

#endif
