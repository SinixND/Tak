#ifndef IG20260222212354
#define IG20260222212354

#include "GameConstantsSystem.h"
#include "unity.h"

void testGetRegularStoneCount( void )
{
    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        10,
        getRegularStoneCount( 3 )
    );
    TEST_ASSERT_EQUAL_INT(
        15,
        getRegularStoneCount( 4 )
    );
    TEST_ASSERT_EQUAL_INT(
        21,
        getRegularStoneCount( 5 )
    );
    TEST_ASSERT_EQUAL_INT(
        30,
        getRegularStoneCount( 6 )
    );
    TEST_ASSERT_EQUAL_INT(
        40,
        getRegularStoneCount( 7 )
    );
    TEST_ASSERT_EQUAL_INT(
        50,
        getRegularStoneCount( 8 )
    );
}

void testGetCapstoneCount( void )
{
    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        0,
        getCapstoneCount( 3 )
    );
    TEST_ASSERT_EQUAL_INT(
        0,
        getCapstoneCount( 4 )
    );
    TEST_ASSERT_EQUAL_INT(
        1,
        getCapstoneCount( 5 )
    );
    TEST_ASSERT_EQUAL_INT(
        1,
        getCapstoneCount( 6 )
    );
    TEST_ASSERT_EQUAL_INT(
        2,
        getCapstoneCount( 7 )
    );
    TEST_ASSERT_EQUAL_INT(
        2,
        getCapstoneCount( 8 )
    );
}

#endif
