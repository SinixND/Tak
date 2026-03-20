#include "RenderSystem.h"

//* Choose backend
#ifdef BACKEND_NCURSES
#include "RenderSystem_NCurses.h"
#endif

void renderApp( App* const app )
{
    render( app );
}

void renderStaticContent( App* const app )
{
    renderStatic( app );
}
