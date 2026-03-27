#ifndef IG20260327200011
#define IG20260327200011

#include "GameEvent.h"
#include <stdbool.h>

/// Return initialized game event object
GameEvent newGameEvent( void );

/// Validate event against game rules
bool validateEvent(
    GameEvent const* const event,
    Game const* const game
);

/// Validate placement event against game rules
bool validateEventPlace(
    GameEvent const* const event,
    Game const* const game
);

/// Validate lift event against game rules
bool validateEventLift(
    GameEvent const* const event,
    Game const* const game
);

/// Validate drop event against game rules
bool validateEventDrop(
    GameEvent const* const event,
    Game const* const game
);

#endif
