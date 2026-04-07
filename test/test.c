#include "TestApp.h"
#include "TestBoard.h"
#include "TestEvent.h"
#include "TestGame.h"
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

    //* Test Event
    RUN_TEST( testNewEvent );

    //* EventExecution
    // TODO:
    // RUN_TEST( testExecuteEvent );
    // RUN_TEST( testApplyEventPlace );
    // RUN_TEST( testApplyEventLift );
    // RUN_TEST( testApplyEventDrop );

    //* Test InputSystem
    RUN_TEST( testHandleGlobalInput );

    //* Test App
    RUN_TEST( testNewApp );

    return UNITY_END();
}
