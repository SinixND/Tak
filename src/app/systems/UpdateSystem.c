#include "UpdateSystem.h"

void updateApp( App* const app )
{
    //* Check for app close input
    app->shoudClose = ( app->inputBuffer.lastInput == INPUT_Q ) ? true : false;
}

