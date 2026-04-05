#ifndef IG20260327150921
#define IG20260327150921

#include "App.h"

/// Return initialized history object
App newApp( int const boardWidth );

/// Setup before running the application loop
void setupApp( void );

/// Run main application loop, ticking frames
void runApp( App* const pApp );

/// Clean up before closing the application
void closeApp( void );

/// Tick next frame
void updateFrame( App* const pApp );

/// Apply game event data to game state
void applyEvent(
    Game* const pGame,
    GameEvent const* const pEvent
);

/// Apply placement event to game state
void applyEventPlace(
    Game* const pGame,
    GameEvent const* const pEvent
);

/// Apply lift event to game state
void applyEventLift(
    Game* const pGame,
    GameEvent const* const pEvent
);

/// Apply drop event to game state
void applyEventDrop(
    Game* const pGame,
    GameEvent const* const pEvent
);

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
