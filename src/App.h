#ifndef IG20260317123947
#define IG20260317123947

#include "AppStateId.h"
#include "Command.h"
#include "Event.h"
#include "Game.h"
#include "InputBuffer.h"
#include <stdbool.h>

typedef struct App
{
    Game game;
    InputBuffer inputBuffer;
    Event event;
    Command command;
    AppStateId state;
    bool shouldClose;
} App;

/// Return initialized App object
App newApp( int const boardSize );

/// Setup before running the application loop
void setupApp( void );

/// Run main application loop, ticking frames
void runApp( App* const pApp );

/// Clean up before closing the application
void closeApp( void );

/// Update one frame of the main loop
void updateFrame( App* const pApp );

/// Update application state
void updateApp( App* const pApp );

#endif
