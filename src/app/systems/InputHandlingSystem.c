#include "InputHandlingSystem.h"

void handleGlobalInput( App* const app )
{
    //* Conditionally terminate by
    //* changing main while loop condition
    app->shoudClose
        = ( app->inputBuffer.lastInput == INPUT_Q )
              ? true
              : false;
}

void handleStateInput( App* const app )
{
    switch ( app - state )
    {
    }
}
