#include "TestGameConstantsSystem.h"
#include "TestGameSystem.h"
#include "TestMatchConfigsSystem.h"
#include "TestPlacementSystem.h"
#include "TestPlayersSystem.h"
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
    RUN_TEST( testGetMatchConfigs );

    //* Test PlacementSystem
    RUN_TEST( testPlaceStoneOnBoard );

    //* Test PlayersSystem
    RUN_TEST( testNewPlayers );
    RUN_TEST( testTakeFromReserves );

    //* Test PositionSystem
    RUN_TEST( testPositionToBoardIndex );

    //* Test StacksSystem
    RUN_TEST( testNewStacks );
    RUN_TEST( testPutStoneOnStack );

    //* Test StackSystem
    RUN_TEST( testNewStack );

    return UNITY_END();
}
