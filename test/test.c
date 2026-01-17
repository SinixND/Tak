#include "TestBoard.h"
#include "TestDefaultSettings.h"
#include "TestPlayers.h"
#include "TestPositionSystem.h"
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
    RUN_TEST( testPositionToBoardIndex );
    RUN_TEST( testGetDefaultSettings );

    return UNITY_END();
}
