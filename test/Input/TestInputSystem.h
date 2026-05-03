#ifndef IG20260327194613
#define IG20260327194613

#include "App.h"
#include "GameConstants.h"
#include "InputId.h"
#include "InputSystem.h"
#include <unity.h>

void testHandleGlobalInput( void )
{
    App app = newApp( BOARD_SIZE_DEFAULT );

    app.inputBuffer.keyboard = INPUT_Q;

    handleGlobalInput( &app );

    TEST_ASSERT_EQUAL_INT( true, app.shouldClose );
}

#endif
