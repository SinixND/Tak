#include "InputSystem.h"
#include <assert.h>

void handleGlobalInput( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    // NOTE: Maybe extract into separate function later
    pApp->shouldClose
        = ( pApp->inputBuffer.keyboard == INPUT_Q )
              ? true
              : false;
}
