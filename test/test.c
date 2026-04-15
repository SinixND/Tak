#include "TestApp.h"
#include "TestBoard.h"
#include "TestCommand.h"
#include "TestDirectionId.h"
#include "TestEvent.h"
#include "TestEventBuilding.h"
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

    //* Position
    RUN_TEST( testPositionToStackIndex );
    RUN_TEST( testSquareToStackIndex );

    //* Board
    RUN_TEST( testNewBoard );
    RUN_TEST( testPlaceOntoStack );
    RUN_TEST( testTakeFromStack );

    //* Reserves
    RUN_TEST( testNewReserves );
    RUN_TEST( testTakeFromReserves );

    //* StackBuffer
    RUN_TEST( testNewStackBuffer );
    RUN_TEST( testResetStackBuffer );
    RUN_TEST( testAppendToBuffer );
    RUN_TEST( testDropFromBuffer );

    //* GameConstants
    RUN_TEST( testGetReservesRegular );
    RUN_TEST( testGetReservesCapstone );
    RUN_TEST( testGetStackCapacity );

    //* Game
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

    //* Command
    RUN_TEST( testNewCommand );
    RUN_TEST( testParseInputActionType );
    RUN_TEST( testParseInputStoneType );
    RUN_TEST( testParseInputFileX );
    RUN_TEST( testParseInputRankY );
    RUN_TEST( testParseInputDirection );
    RUN_TEST( testParseInputFirstDropAmount );
    RUN_TEST( testParseInputDropAmount );
    // RUN_TEST( testBuildCommand );
    RUN_TEST( testIsCommandComplete );

    //* Event
    RUN_TEST( testNewEvent );

    //* Event building
    RUN_TEST( testBuildEvent );

    //* InputSystem
    RUN_TEST( testHandleGlobalInput );

    //* App
    RUN_TEST( testNewApp );

    return UNITY_END();
}
