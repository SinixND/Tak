#include "InputPollingSystem.h"

#include "InputBuffer.h"

//* Choose backend
#ifdef BACKEND_NCURSES
#include "InputSystem_NCurses.h"
#endif

void getInput( InputBuffer* const inputBuffer )
{
    inputBuffer->lastInput = pollInput();
}

