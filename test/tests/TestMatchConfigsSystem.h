#ifndef IG20260104183517
#define IG20260104183517

#include "BoardWidthId.h"
#include "MatchConfigsSystem.h"
#include <unity.h>

void testGetMatchConfigs( void )
{
    //* EXECUTE
    MatchConfigs configs = getMatchConfigs( BWD_3 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( BWD_3, configs.boardWidthId );
    TEST_ASSERT_EQUAL_INT( 10, configs.baseRegularReserves );
    TEST_ASSERT_EQUAL_INT( 0, configs.baseCapstoneReserves );
    TEST_ASSERT_EQUAL_INT( 20, configs.stonesTotal );
    TEST_ASSERT_EQUAL_INT( 9, configs.boardTiles );
    //* EXECUTE
    configs = getMatchConfigs( 4 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( BWD_4, configs.boardWidthId );
    TEST_ASSERT_EQUAL_INT( 15, configs.baseRegularReserves );
    TEST_ASSERT_EQUAL_INT( 0, configs.baseCapstoneReserves );
    TEST_ASSERT_EQUAL_INT( 30, configs.stonesTotal );
    TEST_ASSERT_EQUAL_INT( 16, configs.boardTiles );

    //* EXECUTE
    configs = getMatchConfigs( 5 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( BWD_5, configs.boardWidthId );
    TEST_ASSERT_EQUAL_INT( 21, configs.baseRegularReserves );
    TEST_ASSERT_EQUAL_INT( 1, configs.baseCapstoneReserves );
    TEST_ASSERT_EQUAL_INT( 44, configs.stonesTotal );
    TEST_ASSERT_EQUAL_INT( 25, configs.boardTiles );

    //* EXECUTE
    configs = getMatchConfigs( 6 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( BWD_6, configs.boardWidthId );
    TEST_ASSERT_EQUAL_INT( 30, configs.baseRegularReserves );
    TEST_ASSERT_EQUAL_INT( 1, configs.baseCapstoneReserves );
    TEST_ASSERT_EQUAL_INT( 62, configs.stonesTotal );
    TEST_ASSERT_EQUAL_INT( 36, configs.boardTiles );

    //* EXECUTE
    configs = getMatchConfigs( 7 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( BWD_7, configs.boardWidthId );
    TEST_ASSERT_EQUAL_INT( 40, configs.baseRegularReserves );
    TEST_ASSERT_EQUAL_INT( 2, configs.baseCapstoneReserves );
    TEST_ASSERT_EQUAL_INT( 84, configs.stonesTotal );
    TEST_ASSERT_EQUAL_INT( 49, configs.boardTiles );

    //* EXECUTE
    configs = getMatchConfigs( 8 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( BWD_8, configs.boardWidthId );
    TEST_ASSERT_EQUAL_INT( 50, configs.baseRegularReserves );
    TEST_ASSERT_EQUAL_INT( 2, configs.baseCapstoneReserves );
    TEST_ASSERT_EQUAL_INT( 104, configs.stonesTotal );
    TEST_ASSERT_EQUAL_INT( 64, configs.boardTiles );
}

#endif
