#include "InputPollingSystem.h"

#include "InputBuffer.h"

//* Choose backend
#ifdef BACKEND_NCURSES
#include "InputSystem.h"
#endif

void getInput( InputBuffer* const inputBuffer )
{
    inputBuffer->lastInput = pollInput();
}

