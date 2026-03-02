#include "TestBoardSystem.h"
#include "TestGameConstantsSystem.h"
#include "TestGameSystem.h"
#include "TestMatchConfigsSystem.h"
#include "TestPlayerActionSystem.h"
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

    //* Test BoardSystem
    RUN_TEST( testNewBoard );
    RUN_TEST( testAddStoneToBoard );
    RUN_TEST( testRemoveStoneFromBoard );

    //* Test GameConstantsSystem
    RUN_TEST( testGetBaseRegularStoneReserves );
    RUN_TEST( testGetBaseCapstoneReserves );

    //* Test GameSystem
    RUN_TEST( testNewGame );
    RUN_TEST( testPlayStone );
    RUN_TEST( testUndoPlayStone );
    RUN_TEST( testPickUpStack );

    //* Test MatchConfigsSystem
    RUN_TEST( testGetMatchConfigs );

    //* Test PlayerActionSystem
    RUN_TEST( testNewPlayerActionPlace );
    // RUN_TEST( testNewPlayerActionMove );

    //* Test PlayersSystem
    RUN_TEST( testNewPlayers );
    RUN_TEST( testTakeFromReserves );
    RUN_TEST( testAddToReserves );

    //* Test PositionSystem
    RUN_TEST( testPositionToBoardIndex );

    //* Test StackBufferSystem
    RUN_TEST( testNewStackBuffer );
    RUN_TEST( testAppendToBottom );
    RUN_TEST( testDropFromBottom );

    //* Test StackSystem
    RUN_TEST( testNewStack );
    RUN_TEST( testPutOnTop );
    RUN_TEST( testTakeFromTop );

    return UNITY_END();
}
