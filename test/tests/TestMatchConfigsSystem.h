#ifndef IG20260104183517
#define IG20260104183517

#include "MatchConfigsSystem.h"
#include <unity.h>

void testGetMatchConfigs( void )
{
    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 10, getMatchConfigs( 3 ).regularStonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 0, getMatchConfigs( 3 ).capstonePlayerReserves );

    TEST_ASSERT_EQUAL_INT( 15, getMatchConfigs( 4 ).regularStonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 0, getMatchConfigs( 4 ).capstonePlayerReserves );

    TEST_ASSERT_EQUAL_INT( 21, getMatchConfigs( 5 ).regularStonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 1, getMatchConfigs( 5 ).capstonePlayerReserves );

    TEST_ASSERT_EQUAL_INT( 30, getMatchConfigs( 6 ).regularStonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 1, getMatchConfigs( 6 ).capstonePlayerReserves );

    TEST_ASSERT_EQUAL_INT( 40, getMatchConfigs( 7 ).regularStonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 2, getMatchConfigs( 7 ).capstonePlayerReserves );

    TEST_ASSERT_EQUAL_INT( 50, getMatchConfigs( 8 ).regularStonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 2, getMatchConfigs( 8 ).capstonePlayerReserves );
}

void testGetDefaultMatchConfigs( void )
{
    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 5, getDefaultMatchConfigs().boardWidth );
    TEST_ASSERT_EQUAL_INT( 21, getDefaultMatchConfigs().regularStonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 1, getDefaultMatchConfigs().capstonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 44, getDefaultMatchConfigs().stonesTotal );
    TEST_ASSERT_EQUAL_INT( 25, getDefaultMatchConfigs().boardTiles );
}

void testGetTotalPlayerReserves( void )
{
    //* SETUP
    MatchConfigs matchConstants = {
        1,
        1,
        0,
        1,
        1,
    };

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 1, getTotalPlayerReserves( matchConstants ) );
}
#endif
