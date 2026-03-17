#include "InputBufferSystem.h"

#include "App.h"

//* Choose backend
#ifdef BACKEND_NCURSES
#include "InputSystem_NCurses.h"
#endif

void handleInput( App* const app )
{
    app->input.last = pollInput();
}

