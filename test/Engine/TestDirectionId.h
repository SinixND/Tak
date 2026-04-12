#ifndef IG20260412165854
#define IG20260412165854

#include "DirectionId.h"
#include <unity.h>

void testGetOffsetX( void )
{
    TEST_ASSERT_EQUAL_INT( 0, getOffsetX( DIR_NONE ) );
    TEST_ASSERT_EQUAL_INT( 0, getOffsetX( DIR_DOWN ) );
    TEST_ASSERT_EQUAL_INT( -1, getOffsetX( DIR_LEFT ) );
    TEST_ASSERT_EQUAL_INT( 1, getOffsetX( DIR_RIGHT ) );
    TEST_ASSERT_EQUAL_INT( 0, getOffsetX( DIR_UP ) );
}

void testGetOffsetY( void )
{
    TEST_ASSERT_EQUAL_INT( 0, getOffsetY( DIR_NONE ) );
    TEST_ASSERT_EQUAL_INT( -1, getOffsetY( DIR_DOWN ) );
    TEST_ASSERT_EQUAL_INT( 0, getOffsetY( DIR_LEFT ) );
    TEST_ASSERT_EQUAL_INT( 0, getOffsetY( DIR_RIGHT ) );
    TEST_ASSERT_EQUAL_INT( 1, getOffsetY( DIR_UP ) );
}

#endif
