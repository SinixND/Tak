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

    //* === Unit tests ===

    //* === Entities ===
    //* Test Players
    RUN_TEST( testNewPlayers );

    //* Test Stack
    RUN_TEST( testNewStack );

    //* Test Stacks
    RUN_TEST( testNewStacks );

    //* Test Game
    RUN_TEST( testNewGame );

    //* === Systems ===
    //* Test GameConstantsSystem
    RUN_TEST( testGetRegularStoneCount );
    RUN_TEST( testGetCapstoneCount );

    //* Test MatchConfigs
    RUN_TEST( testDefineMatchConfigs );
    RUN_TEST( testGetTotalPlayerReserves );

    //* Test PositionSystem
    RUN_TEST( testPositionToBoardIndex );

    //* Test StackSystem
    RUN_TEST( testCreateOrGetStackIdx );
    RUN_TEST( testTakeFromReserves );
    RUN_TEST( testPutStoneOnStack );

    //* Test PlayerSystem
    //* Test GameSystem

    //* === Integration tests ===
    //* Test PlacementSystem
    RUN_TEST( testPlaceStoneOnBoard );

    return UNITY_END();
}
