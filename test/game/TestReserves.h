#ifndef IG20260104182445
#define IG20260104182445

#include "PlayerId.h"
#include "Reserves.h"
#include <unity.h>

void testNewReserves( void )
{
    Reserves reserves = newReserves( 3 );

    TEST_ASSERT_EQUAL_INT( 10, reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 10, reserves.regular[PLAYER_BLACK] );
    TEST_ASSERT_EQUAL_INT( 0, reserves.capstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, reserves.capstone[PLAYER_BLACK] );
}

void testTakeFromReserves( void )
{
    Reserves reserves = newReserves( 5 );

    takeFromReserves(
        &reserves,
        PLAYER_WHITE,
        STONE_TYPE_FLAT
    );

    TEST_ASSERT_EQUAL_INT( 20, reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 21, reserves.regular[PLAYER_BLACK] );

    takeFromReserves(
        &reserves,
        PLAYER_BLACK,
        STONE_TYPE_CAP
    );

    TEST_ASSERT_EQUAL_INT( 1, reserves.capstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, reserves.capstone[PLAYER_BLACK] );
}

#endif
