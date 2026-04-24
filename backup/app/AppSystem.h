#ifndef IG20260317220146
#define IG20260317220146

#include "App.h"
#include <stdbool.h>
#include <stdint.h>

App newApp( int const boardSize );

void setupApp( void );
void closeApp( void );

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
void changeState(
    App* const app,
    AppState const state
);

/// State handling
/// White places black flat
void handleStateFirstTurn( App* const app );
/// Black places white flat
void handleStateSecondTurn( App* const app );
/// Choose what game event to prepare
void handleStateChooseAction( App* const app );
/// Get stone type
void handleStateGetStoneType( App* const app );
/// Get column of target square
void handleStateGetFileX( App* const app );
/// Get row of target square
void handleStateGetRankY( App* const app );
/// Get direction to move stack
void handleStateGetDirection( App* const app );
/// Get drop count (can be 0 on initial square)
void handleStateGetFirstDropAmount( App* const app );
/// Get drop count
void handleStateGetDropAmount( App* const app );

/// Check built event serves rules
// TODO:
//  void handleStateEventCheck( App* const app );

/// Execute built game event
void handleStateResolveAction( App* const app );
/// Prepare/Reset data for next turn
void handleStateEndTurn( App* const app );

#endif
