#include "UpdateSystem.h"

void updateApp( App* const app )
{
    app->shoudClose = ( app->input.last == INPUT_Q ) ? true : false;
}

