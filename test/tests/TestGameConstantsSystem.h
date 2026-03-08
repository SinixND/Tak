#ifndef IG20260222212354
#define IG20260222212354

#include "GameConstantsSystem.h"
#include "unity.h"

void testGetBaseRegularStoneReserves( void )
{
    TEST_ASSERT_EQUAL_INT( 10, getBaseRegularStoneReserves( 3 ) );
    TEST_ASSERT_EQUAL_INT( 15, getBaseRegularStoneReserves( 4 ) );
    TEST_ASSERT_EQUAL_INT( 21, getBaseRegularStoneReserves( 5 ) );
    TEST_ASSERT_EQUAL_INT( 30, getBaseRegularStoneReserves( 6 ) );
    TEST_ASSERT_EQUAL_INT( 40, getBaseRegularStoneReserves( 7 ) );
    TEST_ASSERT_EQUAL_INT( 50, getBaseRegularStoneReserves( 8 ) );
}

void testGetBaseCapstoneReserves( void )
{
    TEST_ASSERT_EQUAL_INT( 0, getBaseCapstoneReserves( 3 ) );
    TEST_ASSERT_EQUAL_INT( 0, getBaseCapstoneReserves( 4 ) );
    TEST_ASSERT_EQUAL_INT( 1, getBaseCapstoneReserves( 5 ) );
    TEST_ASSERT_EQUAL_INT( 1, getBaseCapstoneReserves( 6 ) );
    TEST_ASSERT_EQUAL_INT( 2, getBaseCapstoneReserves( 7 ) );
    TEST_ASSERT_EQUAL_INT( 2, getBaseCapstoneReserves( 8 ) );
}

#endif
