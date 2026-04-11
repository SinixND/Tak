#ifndef IG20260410152134
#define IG20260410152134

#include "Command.h"
#include "Event.h"
#include "Game.h"

/// Data for running the game
typedef struct Engine
{
    Event event;
    Command command;
} Engine;

/// Return initialized Engine object
Engine newEngine( void );

/// Update game state with event
void executeEvent(
    Game* const pGame,
    Event const* const pEvent
);

#endif
