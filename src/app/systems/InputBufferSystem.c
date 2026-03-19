#include "InputBufferSystem.h"

#include "InputBuffer.h"

//* Choose backend
#ifdef BACKEND_NCURSES
#include "InputSystem_NCurses.h"
#endif

void bufferInput( InputBuffer* const inputBuffer )
{
    buffer->last = pollInput();
}

