#include "BackendInterface.h"

#ifdef BACKEND_NCURSES
#include <assert.h>
#include <ncurses.h>

void wait( int const ms )
{
    assert(
        ms >= 0
        && "Time value invalid"
    );

    napms( ms );
}

#endif
