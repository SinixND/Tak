#ifndef IG20260327194613
#define IG20260327194613

#include "App.h"
#include "InputParsing.h"
#include "Mappings.h"
#include <unity.h>

void testHandleGlobalInput( void )
{
    App app = newApp();

    app.input.lastInput = app.input.mappings.inputs[CONTEXT_GLOBAL][COMMAND_QUIT];

    handleGlobalInput( &app );

    TEST_ASSERT_EQUAL_INT( true, app.shouldClose );
}

#endif
