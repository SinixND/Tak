#include "FileId.h"
#include "PositionSystem.h"
#include "RankId.h"
#include "unity.h"

void testPositionToBoardIndex( void )
{
    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 0, positionToBoardIndex( FILE_A, RANK_1, BWD_3 ) );
    TEST_ASSERT_EQUAL_INT( 8, positionToBoardIndex( FILE_C, RANK_3, BWD_3 ) );
    TEST_ASSERT_EQUAL_INT( 63, positionToBoardIndex( FILE_H, RANK_8, BWD_8 ) );
}
