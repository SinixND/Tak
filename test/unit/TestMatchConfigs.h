#ifndef IG20260104183517
#define IG20260104183517

#include "MatchConfigs.h"
#include <unity.h>

void testDefineMatchConfigs( void )
{
    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 10, defineMatchConfigs( 3 ).regularStoneReserves );
    TEST_ASSERT_EQUAL_INT( 0, defineMatchConfigs( 3 ).capstoneReserves );

    TEST_ASSERT_EQUAL_INT( 15, defineMatchConfigs( 4 ).regularStoneReserves );
    TEST_ASSERT_EQUAL_INT( 0, defineMatchConfigs( 4 ).capstoneReserves );

    TEST_ASSERT_EQUAL_INT( 21, defineMatchConfigs( 5 ).regularStoneReserves );
    TEST_ASSERT_EQUAL_INT( 1, defineMatchConfigs( 5 ).capstoneReserves );

    TEST_ASSERT_EQUAL_INT( 30, defineMatchConfigs( 6 ).regularStoneReserves );
    TEST_ASSERT_EQUAL_INT( 1, defineMatchConfigs( 6 ).capstoneReserves );

    TEST_ASSERT_EQUAL_INT( 40, defineMatchConfigs( 7 ).regularStoneReserves );
    TEST_ASSERT_EQUAL_INT( 2, defineMatchConfigs( 7 ).capstoneReserves );

    TEST_ASSERT_EQUAL_INT( 50, defineMatchConfigs( 8 ).regularStoneReserves );
    TEST_ASSERT_EQUAL_INT( 2, defineMatchConfigs( 8 ).capstoneReserves );
}

void testGetTotalPlayerReserves( void )
{
    //* SETUP
    MatchConfigs matchConstants = {
        1,
        0
    };

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 1, getTotalPlayerReserves( matchConstants ) );
}
#endif
