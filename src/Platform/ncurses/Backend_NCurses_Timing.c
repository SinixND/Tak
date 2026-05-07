#include "BackendInterface.h"

#include "App.h"
#include <assert.h>
#include <ncurses.h>

#ifdef BACKEND_NCURSES

void loopBackend( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    while ( !pApp->shouldClose )
    {
        updateFrame( pApp );
    }
}

void wait( int const ms )
{
    napms( ms );
}

#endif
