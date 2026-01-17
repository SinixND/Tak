#include "GameSettings.h"
#include "unity.h"

void testGetDefaultSettings( void )
{
    TEST_ASSERT_EQUAL_INT( 5, getDefaultSettings().boardWidth );
}
