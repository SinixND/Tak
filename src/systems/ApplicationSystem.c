#include "ApplicationSystem.h"

#include "Application.h"
#include "GameEventSystem.h"
#include "GameSystem.h"

#ifdef BACKEND_NCURSES
#include "ncursesBackend.h"
#endif

Application newApp( void )
{
    Application app = {
        .game = newGame( 0 ),
        .gameEvent = newGameEvent(),
    };

    return app;
}

void runApp( Application* const app )
{
    initBackend();

    *app = runMainLoop( *app );

    deinitBackend();
}
