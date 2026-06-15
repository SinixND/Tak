#ifndef IG20260411152411
#define IG20260411152411

#include "GameConstants.h"
#include <unity.h>

void testGetReservesRegular( void )
{
    TEST_ASSERT_EQUAL_INT( 10, getReservesRegular( 3 ) );
    TEST_ASSERT_EQUAL_INT( 15, getReservesRegular( 4 ) );
    TEST_ASSERT_EQUAL_INT( 21, getReservesRegular( 5 ) );
    TEST_ASSERT_EQUAL_INT( 30, getReservesRegular( 6 ) );
    TEST_ASSERT_EQUAL_INT( 40, getReservesRegular( 7 ) );
    TEST_ASSERT_EQUAL_INT( 50, getReservesRegular( 8 ) );
}

void testGetReservesCapstone( void )
{
    TEST_ASSERT_EQUAL_INT( 0, getReservesCapstone( 3 ) );
    TEST_ASSERT_EQUAL_INT( 0, getReservesCapstone( 4 ) );
    TEST_ASSERT_EQUAL_INT( 1, getReservesCapstone( 5 ) );
    TEST_ASSERT_EQUAL_INT( 1, getReservesCapstone( 6 ) );
    TEST_ASSERT_EQUAL_INT( 2, getReservesCapstone( 7 ) );
    TEST_ASSERT_EQUAL_INT( 2, getReservesCapstone( 8 ) );
}

void testGetStackCapacity( void )
{
    TEST_ASSERT_EQUAL_INT( 20, getStackCapacity( 3 ) );
    TEST_ASSERT_EQUAL_INT( 30, getStackCapacity( 4 ) );
    TEST_ASSERT_EQUAL_INT( 43, getStackCapacity( 5 ) );
    TEST_ASSERT_EQUAL_INT( 61, getStackCapacity( 6 ) );
    TEST_ASSERT_EQUAL_INT( 81, getStackCapacity( 7 ) );
    TEST_ASSERT_EQUAL_INT( 101, getStackCapacity( 8 ) );
}

#endif
