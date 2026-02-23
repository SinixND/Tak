#include "TestGameConstantsSystem.h"
#include "TestGameSystem.h"
#include "TestMatchConfigsSystem.h"
#include "TestPlacementSystem.h"
#include "TestPlayerSystem.h"
#include "TestPositionSystem.h"
#include "TestStackSystem.h"
#include "TestStacksSystem.h"
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
    RUN_TEST( testDefineMatchConfigs );
    RUN_TEST( testGetTotalPlayerReserves );

    //* Test PlacementSystem
    RUN_TEST( testPlaceStoneOnBoard );

    //* Test PlayersSystem
    RUN_TEST( testNewPlayers );

    //* Test PositionSystem
    RUN_TEST( testPositionToBoardIndex );

    //* Test StackSystem
    RUN_TEST( testNewStack );

    //* Test StacksSystem
    RUN_TEST( testNewStacks );
    RUN_TEST( testCreateOrGetStackIdx );
    RUN_TEST( testTakeFromReserves );
    RUN_TEST( testPutStoneOnStack );

    return UNITY_END();
}
