#ifndef IG20260406172501
#define IG20260406172501

#include "App.h"

/// Update app state with game event
void executeTurn( App* const pApp );

/// Apply placement event to game state
void applyEventPlace( App* const pApp );

/// Apply lift event to game state
void applyEventLift( App* const pApp );

/// Apply drop event to game state
void applyEventDrop( App* const pApp );

#endif
