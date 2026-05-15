#ifndef IG20260327194613
#define IG20260327194613

#include "App.h"
#include "GameConstants.h"
#include "InputSystem.h"
#include "Keymap.h"
#include <unity.h>

void testHandleGlobalInput( void )
{
    App app = newApp();

    app.inputBuffer.lastInput = app.inputBuffer.keymap.inputs[CONTEXT_GLOBAL][COMMAND_QUIT];

    handleGlobalInput( &app );

    TEST_ASSERT_EQUAL_INT( true, app.shouldClose );
}

#endif
