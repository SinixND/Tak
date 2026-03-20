#include "AppSystem.h"

#include "App.h"
#include "AppState.h"
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
        .inputBuffer = { .lastInput = INPUT_NONE },
        .state = STATE_FIRST_TURN_CHOOSE_FILE_X,
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

