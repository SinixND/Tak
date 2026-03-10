#include "TestBoardSystem.h"
#include "TestGameConstantsSystem.h"
#include "TestGameSystem.h"
#include "TestHistorySystem.h"
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
    RUN_TEST( testPlaceOntoStack );
    RUN_TEST( testTakeFromStack );

    //* Test GameConstantsSystem
    RUN_TEST( testGetBaseRegularStoneReserves );
    RUN_TEST( testGetBaseCapstoneReserves );

    //* Test GameSystem
    RUN_TEST( testNewGame );
    RUN_TEST( testPlaceStone );
    RUN_TEST( testPickUpStack );
    RUN_TEST( testDropStone );
    RUN_TEST( testUndoPlaceStone );
    RUN_TEST( testUndo );

    //* Test HistorySystem
    RUN_TEST( testRecordPlacementAction );
    RUN_TEST( testRecordPickUpAction );
    RUN_TEST( testUndoHistory );
    RUN_TEST( testRedoHistory );

    //* Test PlayersSystem
    RUN_TEST( testNewPlayers );
    RUN_TEST( testTakeFromReserves );

    //* Test PositionSystem
    RUN_TEST( testPositionToStackIndex );

    //* Test StackBufferSystem
    RUN_TEST( testNewStackBuffer );
    RUN_TEST( testResetStackBuffer );
    RUN_TEST( testAppendToBuffer );
    RUN_TEST( testDropFromBuffer );

    return UNITY_END();
}
