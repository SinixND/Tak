#ifndef IG20260406172501
#define IG20260406172501

#include "Game.h"
#include "GameEvent.h"

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

#endif
