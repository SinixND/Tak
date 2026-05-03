#ifndef IG20260317123947
#define IG20260317123947

#include "AppStateId.h"
#include "Command.h"
#include "Event.h"
#include "Game.h"
#include "InputBuffer.h"
#include "Prompt.h"
#include <stdbool.h>

typedef struct App
{
    /// State
    AppStateId state;
    /// Core
    Game game;
    /// Input
    InputBuffer inputBuffer;
    /// Engine
    Command command;
    Event event;
    /// Render
    Prompt prompt;
    /// Timing
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

/// Handle app state
void handleAppStateNormalTurn( App* const pApp );

/// Get input and update dependent data
void handleInput( App* const pApp );

/// Update application state
void updateApp( App* const pApp );

/*
 * @brief: Modify game state from command
 *
 * Returns true if game was updated
 */
bool updateGame( App* const pApp );

/*
 * @brief: Check if current player turn is complete
 *
 * Uses command state to check
 */
bool isTurnComplete( App const* const pApp );

/// Perform actions to prepare next turn
void prepareNextTurn( App* const pApp );

#endif
