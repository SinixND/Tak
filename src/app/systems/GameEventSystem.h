#ifndef IG20260327200011
#define IG20260327200011

#include "Board.h"
#include "Game.h"
#include "GameEvent.h"
#include "Players.h"
#include "StackBuffer.h"
#include <stdbool.h>

/// Return initialized game event object
GameEvent newGameEvent( void );

/// Validate event against game rules
bool validateEvent(
    GameEvent const* const pEvent,
    Game const* const pGame
);

#endif
