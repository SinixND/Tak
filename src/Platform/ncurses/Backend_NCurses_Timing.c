#include "BackendInterface.h"

#include "App.h"
#include <assert.h>

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

#endif
