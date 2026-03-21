#ifndef IG20260317220146
#define IG20260317220146

#include "App.h"
#include "Game.h"
#include "GameEvent.h"
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

void updateStateFirstTurnChooseFileX( App* const app );
void updateStateFirstTurnChooseRankY( App* const app );
void updateStateSecondTurnChooseFileX( App* const app );
void updateStateSecondTurnChooseRankY( App* const app );
void updateStateChooseAction( App* const app );
void updateStateChooseStoneType( App* const app );
void updateStateChooseFileX( App* const app );
void updateStateChooseRankY( App* const app );
void updateStateChooseDirection( App* const app );
void updateStateChooseFirstDropAmount( App* const app );
void updateStateChooseAmount( App* const app );
void updateStateUpdateGame( App* const app );
void updateStateEndTurn( App* const app );

void appendToCurrentInput(
    char* currentInput,
    int8_t* const inputLength,
    char const ch
);

#endif
