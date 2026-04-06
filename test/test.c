#include "TestApp.h"
#include "TestBoard.h"
#include "TestGame.h"
#include "TestGameEvent.h"
#include "TestGameEventValidation.h"
#include "TestHistory.h"
#include "TestInputSystem.h"
#include "TestPositionSystem.h"
#include "TestReserves.h"
#include "TestStackBuffer.h"
#include <unity.h>

void setUp( void ) {}

void tearDown( void ) {}

int main( void )
{
    UNITY_BEGIN();

    //* Test Board
    RUN_TEST( testNewBoard );
    RUN_TEST( testPlaceOntoStack );
    RUN_TEST( testTakeFromStack );

    //* Test Game
    RUN_TEST( testNewGame );
    RUN_TEST( testPlaceStone );
    RUN_TEST( testTakeStone );
    RUN_TEST( testLiftStack );
    RUN_TEST( testDropStack );
    RUN_TEST( testDropStone );
    RUN_TEST( testLiftStone );

    //* Test History
    RUN_TEST( testRecordActionPlacement );
    RUN_TEST( testRecordActionLift );
    RUN_TEST( testRecordActionDrop );
    RUN_TEST( testUndoHistory );
    RUN_TEST( testRedoHistory );

    //* Test Reserves
    RUN_TEST( testNewReserves );
    RUN_TEST( testTakeFromReserves );

    //* Test PositionSystem
    RUN_TEST( testPositionToStackIndex );

    //* Test StackBuffer
    RUN_TEST( testNewStackBuffer );
    RUN_TEST( testResetStackBuffer );
    RUN_TEST( testAppendToBuffer );
    RUN_TEST( testDropFromBuffer );

    //* Test App
    RUN_TEST( testNewApp );

    //* Test InputSystem
    RUN_TEST( testHandleGlobalInput );

    //* Test GameEvent
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
    RUN_TEST( testValidateEventDrop );

    return UNITY_END();
}
