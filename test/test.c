#include "TestAppSystem.h"
#include "TestBoardSystem.h"
#include "TestGameEventSystem.h"
#include "TestGameSystem.h"
#include "TestHistorySystem.h"
#include "TestInputSystem.h"
#include "TestPositionSystem.h"
#include "TestReservesSystem.h"
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

    //* Test GameSystem
    RUN_TEST( testNewGame );
    RUN_TEST( testPlaceStone );
    RUN_TEST( testUndoPlaceStone );
    RUN_TEST( testRedoPlaceStone );
    RUN_TEST( testLiftStack );
    RUN_TEST( testUndoLiftStack );
    RUN_TEST( testRedoLiftStack );
    RUN_TEST( testDropStone );
    RUN_TEST( testUndo );
    RUN_TEST( testRedo );

    //* Test HistorySystem
    RUN_TEST( testRecordPlacementAction );
    RUN_TEST( testRecordLiftAction );
    RUN_TEST( testRecordDropAction );
    RUN_TEST( testUndoHistory );
    RUN_TEST( testRedoHistory );

    //* Test ReservesSystem
    RUN_TEST( testNewReserves );
    RUN_TEST( testTakeFromReserves );

    //* Test PositionSystem
    RUN_TEST( testPositionToStackIndex );

    //* Test StackBufferSystem
    RUN_TEST( testNewStackBuffer );
    RUN_TEST( testResetStackBuffer );
    RUN_TEST( testAppendToBuffer );
    RUN_TEST( testDropFromBuffer );

    //* Test AppSystem
    RUN_TEST( testNewApp );

    //* Test InputSystem
    RUN_TEST( testHandleGlobalInput );

    //* Test GameEventSystem
    RUN_TEST( testNewGameEvent );
    RUN_TEST( testIsStoneTypeAvailable );
    RUN_TEST( testIsFileXOnBoard );
    RUN_TEST( testIsRankYOnBoard );
    RUN_TEST( testIsSquareEmpty );
    RUN_TEST( testDoesPlayerOwnStack );
    RUN_TEST( testIsCaptiveValid );
    RUN_TEST( testIsDropCountValid );
    RUN_TEST( testValidateEventPlace );
    RUN_TEST( testValidateEventLift );

    return UNITY_END();
}
