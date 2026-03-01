#include "TestBoardSystem.h"
#include "TestGameConstantsSystem.h"
#include "TestGameSystem.h"
#include "TestMatchConfigsSystem.h"
#include "TestPlayerActionsSystem.h"
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
    RUN_TEST( testGetBaseRegularStoneReserves );
    RUN_TEST( testGetBaseCapstoneReserves );

    //* Test GameSystem
    RUN_TEST( testNewGame );

    //* Test MatchConfigsSystem
    RUN_TEST( testGetMatchConfigs );

    //* Test PlayerActionsSystem
    RUN_TEST( testPlayStone );

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
