#include "LoopSystem.h"

#include "AppSystem.h"

#ifdef BACKEND_NCURSES
#include <ncurses.h>

void loopBackend( App* const app )
{
    while ( !app->shouldClose )
    {
        updateFrame( app );
    }
}

#endif
