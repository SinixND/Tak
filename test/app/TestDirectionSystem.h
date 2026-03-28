#ifndef IG20260328122528
#define IG20260328122528

#include "DirectionId.h"
#include "DirectionSystem.h"
#include <unity.h>

void testGetOffsetX( void )
{
    TEST_ASSERT_EQUAL_INT( -1, getOffsetX( DIR_LEFT ) );
    TEST_ASSERT_EQUAL_INT( 1, getOffsetX( DIR_RIGHT ) );
    TEST_ASSERT_EQUAL_INT( 0, getOffsetX( DIR_DOWN ) );
    TEST_ASSERT_EQUAL_INT( 0, getOffsetX( DIR_UP ) );
}

void testGetOffsetY( void )
{
    TEST_ASSERT_EQUAL_INT( 0, getOffsetY( DIR_LEFT ) );
    TEST_ASSERT_EQUAL_INT( 0, getOffsetY( DIR_RIGHT ) );
    TEST_ASSERT_EQUAL_INT( -1, getOffsetY( DIR_DOWN ) );
    TEST_ASSERT_EQUAL_INT( 1, getOffsetY( DIR_UP ) );
}

#endif
