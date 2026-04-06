#include "TestApp.h"
#include "TestBoard.h"
#include "TestEvent.h"
#include "TestGame.h"
#include "TestHistory.h"
#include "TestInputSystem.h"
#include "TestPositionSystem.h"
#include "TestReserves.h"
#include "TestRuleValidation.h"
#include "TestStackBuffer.h"
#include <unity.h>

void setUp( void ) {}

void tearDown( void ) {}

int main( void )
{
    UNITY_BEGIN();

    //* Test PositionSystem
    RUN_TEST( testPositionToStackIndex );

    //* Test Board
    RUN_TEST( testNewBoard );
    RUN_TEST( testPlaceOntoStack );
    RUN_TEST( testTakeFromStack );

    //* Test Reserves
    RUN_TEST( testNewReserves );
    RUN_TEST( testTakeFromReserves );

    //* Test StackBuffer
    RUN_TEST( testNewStackBuffer );
    RUN_TEST( testResetStackBuffer );
    RUN_TEST( testAppendToBuffer );
    RUN_TEST( testDropFromBuffer );

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
    // TODO:
    //  RUN_TEST( testUndo );
    //  RUN_TEST( testRedo );

    //* Test InputSystem
    RUN_TEST( testHandleGlobalInput );

    //* Test Event
    RUN_TEST( testNewEvent );

    //* Test RuleValidation
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

    //* TurnExecution
    // TODO:
    // RUN_TEST( testExecuteTurn );
    // RUN_TEST( testApplyEventPlace );
    // RUN_TEST( testApplyEventLift );
    // RUN_TEST( testApplyEventDrop );

    //* Test App
    RUN_TEST( testNewApp );

    return UNITY_END();
}
