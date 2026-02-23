#ifndef IG20260104183517
#define IG20260104183517

#include "MatchConfigsSystem.h"
#include <unity.h>

void testGetMatchConfigs( void )
{
    //* EXECUTE
    MatchConfigs configs = getMatchConfigs(3);

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 3, configs.boardWidth );
    TEST_ASSERT_EQUAL_INT( 10, configs.regularStonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 0, configs.capstonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 20, configs.stonesTotal );
    TEST_ASSERT_EQUAL_INT( 9, configs.boardTiles );

    //* EXECUTE
    configs = getMatchConfigs(4);

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 4, configs.boardWidth );
    TEST_ASSERT_EQUAL_INT( 15, configs.regularStonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 0, configs.capstonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 30, configs.stonesTotal );
    TEST_ASSERT_EQUAL_INT( 16, configs.boardTiles );

    //* EXECUTE
    configs = getMatchConfigs(5);

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 5, configs.boardWidth );
    TEST_ASSERT_EQUAL_INT( 21, configs.regularStonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 1, configs.capstonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 44, configs.stonesTotal );
    TEST_ASSERT_EQUAL_INT( 25, configs.boardTiles );

    //* EXECUTE
    configs = getMatchConfigs(6);

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 6, configs.boardWidth );
    TEST_ASSERT_EQUAL_INT( 30, configs.regularStonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 1, configs.capstonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 62, configs.stonesTotal );
    TEST_ASSERT_EQUAL_INT( 36, configs.boardTiles );

    //* EXECUTE
    configs = getMatchConfigs(7);

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 7, configs.boardWidth );
    TEST_ASSERT_EQUAL_INT( 40, configs.regularStonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 2, configs.capstonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 84, configs.stonesTotal );
    TEST_ASSERT_EQUAL_INT( 49, configs.boardTiles );

    //* EXECUTE
    configs = getMatchConfigs(8);

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 8, configs.boardWidth );
    TEST_ASSERT_EQUAL_INT( 50, configs.regularStonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 2, configs.capstonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 104, configs.stonesTotal );
    TEST_ASSERT_EQUAL_INT( 64, configs.boardTiles );
}

void testGetDefaultMatchConfigs( void )
{
    //* EXECUTE
    MatchConfigs configs = getMatchConfigs(5);

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 5, configs.boardWidth );
    TEST_ASSERT_EQUAL_INT( 21, configs.regularStonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 1, configs.capstonePlayerReserves );
    TEST_ASSERT_EQUAL_INT( 44, configs.stonesTotal );
    TEST_ASSERT_EQUAL_INT( 25, configs.boardTiles );
}

void testGetTotalPlayerReserves( void )
{
    //* EXECUTE
    MatchConfigs configs = getMatchConfigs(5);

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 22, getTotalPlayerReserves( configs ) );
}
#endif
