#include "PositionSystem.h"
#include "unity.h"

void testPositionToBoardIndex( void )
{
    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 0, positionToBoardIndex( 0, 0, 3 ) );
    TEST_ASSERT_EQUAL_INT( 8, positionToBoardIndex( 2, 2, 3 ) );
    TEST_ASSERT_EQUAL_INT( 62, positionToBoardIndex( 6, 7, 8 ) );
}
