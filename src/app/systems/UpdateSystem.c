#include "UpdateSystem.h"

void updateApp( App* const app )
{
    //* Check for app close input
    app->shoudClose = ( app->input.last == INPUT_Q ) ? true : false;
}

