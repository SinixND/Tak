#include "PlatformInterface.h"

#ifdef PLATFORM_UNIX
#include "App.h"
#include <assert.h>

void loop( App* const pApp )
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
