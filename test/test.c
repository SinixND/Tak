#include "TestBoard.h"
#include "TestPlayers.h"
#include "TestStacks.h"
#include "TestStones.h"
#include <unity.h>

void setUp( void ) {}

void tearDown( void ) {}

int main( void )
{
    UNITY_BEGIN();

    //* Unit tests
    RUN_TEST( testInitBoard );
    RUN_TEST( testInitPlayers );
    RUN_TEST( testInitStacks );
    RUN_TEST( testInitStones );

    return UNITY_END();
}
