#include "BackendInterface.h"

#include <assert.h>
#include <ncurses.h>

#ifdef BACKEND_NCURSES

void wait( int const ms )
{
    assert(
        ms >= 0
        && "Time value invalid"
    );

    napms( ms );
}

#endif
