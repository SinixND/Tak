#include "ColumnId.h"
#include "PositionSystem.h"
#include "RowId.h"
#include "unity.h"

void testPositionToBoardIndex( void )
{
    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 0, positionToBoardIndex( COL_A, ROW_1, BWD_3 ) );
    TEST_ASSERT_EQUAL_INT( 8, positionToBoardIndex( COL_C, ROW_3, BWD_3 ) );
    TEST_ASSERT_EQUAL_INT( 63, positionToBoardIndex( COL_H, ROW_8, BWD_8 ) );
}
