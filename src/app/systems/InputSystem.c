#include "InputSystem.h"

void handleGlobalInput( App* const app )
{
    //* NOTE: Maybe extract into separate function later
    app->shouldClose
        = ( app->input.keyboard == INPUT_Q )
              ? true
              : false;
}
