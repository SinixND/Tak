#ifndef IG20260317123947
#define IG20260317123947

#include "Event.h"
#include "Game.h"
#include "History.h"
#include "InputBuffer.h"
#include <stdbool.h>

typedef struct App
{
    Game game;
    InputBuffer inputBuffer;
    Event gameEvent;
    History history;
    bool shouldClose;
} App;

/// Return initialized App object
App newApp( int const boardWidth );

/// Setup before running the application loop
void setupApp( void );

/// Run main application loop, ticking frames
void runApp( App* const pApp );

/// Clean up before closing the application
void closeApp( void );

/// Tick next frame
void updateFrame( App* const pApp );

#endif
