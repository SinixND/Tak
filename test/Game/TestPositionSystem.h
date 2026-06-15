#include "FileId.h"
#include "Position.h"
#include "RankId.h"
#include "unity.h"

void testPositionToStackIndex( void )
{
    TEST_ASSERT_EQUAL_INT( 0, positionToSquare( FILE_A, RANK_1, 3 ) );
    TEST_ASSERT_EQUAL_INT( 8, positionToSquare( FILE_C, RANK_3, 3 ) );
    TEST_ASSERT_EQUAL_INT( 63, positionToSquare( FILE_H, RANK_8, 8 ) );
}

void testSquareToStackIndex( void )
{
    TEST_ASSERT_EQUAL_INT( 0, squareToStackIndex( 0, 3 ) );
    TEST_ASSERT_EQUAL_INT( 160, squareToStackIndex( 8, 3 ) );
    TEST_ASSERT_EQUAL_INT( 1032, squareToStackIndex( 24, 5 ) );
    TEST_ASSERT_EQUAL_INT( 6363, squareToStackIndex( 63, 8 ) );
}

