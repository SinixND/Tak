#include "TestApp.h"
#include "TestBoard.h"
#include "TestCommand.h"
#include "TestDirectionId.h"
#include "TestEvent.h"
#include "TestGame.h"
#include "TestGameConstants.h"
#include "TestInputSystem.h"
#include "TestPositionSystem.h"
#include "TestReserves.h"
#include "TestStackBuffer.h"
#include <unity.h>
#include <unity_internals.h>

void setUp( void ) {}

void tearDown( void ) {}

int main( void )
{
    UNITY_BEGIN();

    //* Test Position
    RUN_TEST( testPositionToStackIndex );
    RUN_TEST( testSquareToStackIndex );

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
    RUN_TEST( testExecuteEvent );

    //* DirectionId
    RUN_TEST( testGetOffsetX );
    RUN_TEST( testGetOffsetY );

    //* Test Command
    RUN_TEST( testNewCommand );
    RUN_TEST( testParseInputAction );
    RUN_TEST( testParseInputStoneType );
    RUN_TEST( testHandleStateGetAction );
    RUN_TEST( testHandleStateGetStoneType );
    // RUN_TEST( testRunBuildCommandFSM );
    RUN_TEST( testIsCommandComplete );

    //* Test Event
    RUN_TEST( testNewEvent );
    RUN_TEST( testBuildEvent );

    //* Test InputSystem
    RUN_TEST( testHandleGlobalInput );

    //* Test App
    RUN_TEST( testNewApp );

    return UNITY_END();
}
