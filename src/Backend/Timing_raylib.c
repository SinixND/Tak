#include "BackendInterface.h"

#ifdef BACKEND_RAYLIB
#include <assert.h>
#include <raylib.h>

void wait( int const ms )
{
    assert(
        ms >= 0
        && "Time value invalid"
    );

    WaitTime( ms / 1000.0f );
}

#endif
