#include "InputSystem.h"
#include "InputBuffer.h"
#include "Keymap.h"

#include <assert.h>

void handleGlobalInput( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    // NOTE: Maybe extract into separate function later
    pApp->shouldClose
        = ( getCommandId(
                &pApp->inputBuffer,
                CONTEXT_GLOBAL
            )
            == COMMAND_QUIT )
              ? true
              : false;
}
