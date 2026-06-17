#ifndef IG20260317123947
#define IG20260317123947

#include "AppStateId.h"
#include "Command.h"
#include "Event.h"
#include "Game.h"
#include "History.h"
#include "InputBuffer.h"
#include "Prompts.h"
#include "Simulation.h"
#include <stdbool.h>

/// Application head structure
typedef struct App
{
    /// State
    AppStateId state;
    /// Core
    Game game;
    /// Input
    InputBuffer inputBuffer;
    Simulation simulation;
    /// Engine
    Command command;
    Event event;
    History history;
    /// Render
    Prompts prompts;
    /// Timing
    bool shouldClose;
} App;

/// Return initialized object
App newApp( void );

/// Setup before running the application loop
void setupApp( void );

/// Run main application loop, ticking frames
void runApp( App* const pApp );

/// Clean up before closing the application
void closeApp( void );

/// Update one frame of the main loop
void updateFrame( App* const pApp );

/// Set board size at game start from user input
bool setBoardSize( App* const pApp );

/// Handle app state
void progressTurn( App* const pApp );

/// Get input (simulated or polled)
void getInput( App* const pApp );

/// Get input and update dependent data
void handleInput( App* const pApp );

/// Update application state
void updateApp( App* const pApp );

/*
 * @brief Modify game state from command
 *
 * Returns true if game was updated
 */
bool updateGame( App* const pApp );

/*
 * @brief Check if current player turn is complete
 *
 * Uses command state to check
 */
bool isTurnComplete( App const* const pApp );

/// Check if and which player won
bool handleGameEnd( App* const pApp );

/// Perform actions to prepare next turn
void handleTurnEnd( App* const pApp );

#endif
