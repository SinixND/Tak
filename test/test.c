#include "TestApp.h"
#include "TestBoard.h"
#include "TestCommand.h"
#include "TestEngine.h"
#include "TestEvent.h"
#include "TestEventExecution.h"
#include "TestGame.h"
#include "TestGameConstants.h"
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

    //* Test GameConstants
    RUN_TEST( testGetReservesRegular );
    RUN_TEST( testGetReservesCapstone );
    RUN_TEST( testGetStackCapacity );

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

    //* Test Command
    RUN_TEST( testNewCommand );
    RUN_TEST( testIsCommandComplete );

    //* Test Engine
    // TODO:
    RUN_TEST( testNewEngine );
    RUN_TEST( testExecuteEvent );

    //* Test InputSystem
    RUN_TEST( testHandleGlobalInput );

    //* Test App
    RUN_TEST( testNewApp );

    return UNITY_END();
}
