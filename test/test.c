#include "TestBoardSystem.h"
#include "TestGameConstantsSystem.h"
#include "TestGameSystem.h"
#include "TestMatchConfigsSystem.h"
#include "TestPlacementSystem.h"
#include "TestPlayersSystem.h"
#include "TestPositionSystem.h"
#include "TestStackBufferSystem.h"
#include "TestStackSystem.h"
#include <unity.h>

void setUp( void ) {}

void tearDown( void ) {}

int main( void )
{
    UNITY_BEGIN();

    //* Test GameConstantsSystem
    RUN_TEST( testGetRegularStoneCount );
    RUN_TEST( testGetCapstoneCount );

    //* Test GameSystem
    RUN_TEST( testNewGame );

    //* Test MatchConfigsSystem
    RUN_TEST( testGetMatchConfigs );

    //* Test PlacementSystem
    RUN_TEST( testPlaceStoneOnBoard );

    //* Test PlayersSystem
    RUN_TEST( testNewPlayers );
    RUN_TEST( testTakeFromReserves );

    //* Test PositionSystem
    RUN_TEST( testPositionToBoardIndex );

    //* Test BoardSystem
    RUN_TEST( testNewBoard );
    RUN_TEST( testPutStoneOnStack );

    //* Test StackBufferSystem
    RUN_TEST( testNewStackBuffer );

    //* Test StackSystem
    RUN_TEST( testNewStack );

    return UNITY_END();
}
