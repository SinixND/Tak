#include "FileId.h"
#include "PositionSystem.h"
#include "RankId.h"
#include "unity.h"

void testPositionToStackIndex( void )
{
    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 0, positionToStackIndex( FILE_A, RANK_1, 3 ) );
    TEST_ASSERT_EQUAL_INT( 8, positionToStackIndex( FILE_C, RANK_3, 3 ) );
    TEST_ASSERT_EQUAL_INT( 63, positionToStackIndex( FILE_H, RANK_8, 8 ) );
}
