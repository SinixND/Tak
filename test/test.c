#include "TestBoardSystem.h"
#include "TestGameConstantsSystem.h"
#include "TestGameSystem.h"
#include "TestPlayersSystem.h"
#include "TestPositionSystem.h"
#include "TestStackBufferSystem.h"
#include <unity.h>

void setUp( void ) {}

void tearDown( void ) {}

int main( void )
{
    UNITY_BEGIN();

    //* Test BoardSystem
    RUN_TEST( testNewBoard );
    RUN_TEST( testPlaceStoneOnBoard );
    RUN_TEST( testPushOntoStack );
    RUN_TEST( testPopFromStack );

    //* Test GameConstantsSystem
    RUN_TEST( testGetBaseRegularStoneReserves );
    RUN_TEST( testGetBaseCapstoneReserves );

    //* Test GameSystem
    RUN_TEST( testNewGame );
    RUN_TEST( testPlaceStone );

    //* Test PlayersSystem
    RUN_TEST( testNewPlayers );
    RUN_TEST( testTakeFromReserves );

    //* Test PositionSystem
    RUN_TEST( testPositionToStackIndex );

    //* Test StackBufferSystem
    RUN_TEST( testNewStackBuffer );
    RUN_TEST( testResetStackBuffer );
    RUN_TEST( testPushOntoBuffer );

    return UNITY_END();
}
