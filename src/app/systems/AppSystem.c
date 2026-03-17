#include "AppSystem.h"

#include "App.h"
#include "GameSystem.h"
#include <assert.h>

//* Choose backend
#ifdef BACKEND_NCURSES
#include "ContextSystem_NCurses.h"
#endif

App newApp( int const boardWidth )
{
    App app = {
        .game = newGame( boardWidth ),
        .input = { .last = INPUT_NONE },
        .shoudClose = false,
    };

    return app;
}

void initApp( void )
{
    initBackend();
}

void deinitApp( void )
{
    deinitBackend();
}

