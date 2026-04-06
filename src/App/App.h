#ifndef IG20260317123947
#define IG20260317123947

#include "Game.h"
#include "GameEvent.h"
#include "History.h"
#include "InputBuffer.h"
#include <stdbool.h>

typedef struct App
{
    Game game;
    InputBuffer inputBuffer;
    GameEvent gameEvent;
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

//* TODO: Extract into module/*systems
/**
 * @brief: Undo last action performed by a player
 *
 * - Read history
 * - Change game state
 * - Adjust history index
 */
// void undo( App* const pApp );

/**
 * @brief: Redo next action performed by a player
 *
 * - Read history
 * - Change game state
 * - Adjust history index
 */
// void redo( App* const pApp );

#endif
