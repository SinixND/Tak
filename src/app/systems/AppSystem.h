#ifndef IG20260317220146
#define IG20260317220146

#include "App.h"
#include "AppState.h"
#include <stdbool.h>
#include <stdint.h>

App newApp( int const boardWidth );

void initApp( void );
void deinitApp( void );

/// Handle input independent of app state
void handleGlobalInput( App* const app );

/**
 * @brief: Updates the application based on input
 *
 * - Parses state independent input
 * - Parses state dependent input
 * - Updates app state
 * - Updates game
 */
void updateApp( App* const app );

void updateState( App* const app );
/// Resets phase
void changeState(
    App* const app,
    AppState const state
);

//* State handling
/// White places black flat
void handleStateFirstTurn( App* const app );
/// Black places white flat
void handleStateSecondTurn( App* const app );
/// Choose what game event to prepare
void handleStateChooseAction( App* const app );
/// Get data for stone placement
void handleStatePrepareEventPlace( App* const app );
/// Get data for stack lift
void handleStatePrepareEventLift( App* const app );
/// Get data for stone drops from lifted stack
void handleStatePrepareEventDrop( App* const app );
/// Check built event serves rules
// TODO:
//  void handleStateEventCheck( App* const app );

/// Execute built game event
void handleStateUpdateGame( App* const app );
/// Prepare/Reset data for next turn
void handleStateEndTurn( App* const app );

//* Return true if successful
/// Get stone type
bool handleInputStoneType( App* const app );
/// Get column of target square
bool handleInputFileX( App* const app );
/// Get row of target square
bool handleInputRankY( App* const app );
/// Get direction to move stack
bool handleInputDirection( App* const app );
/// Get drop count (can be 0 on initial square)
bool handleInputFirstDropAmount( App* const app );
/// Get drop count
bool handleInputDropAmount( App* const app );

#endif
