#include "InputSystem.h"

void handleGlobalInput( App* const pApp )
{
    //* NOTE: Maybe extract into separate function later
    pApp->shouldClose
        = ( pApp->inputBuffer.keyboard == INPUT_Q )
              ? true
              : false;
}
