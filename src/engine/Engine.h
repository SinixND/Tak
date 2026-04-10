#ifndef IG20260410152134
#define IG20260410152134

#include "Command.h"
#include "Event.h"

/// Data for running the game
typedef struct Engine
{
    Event event;
    Command command;
} Engine;

/// Return initialized Engine object
Engine newEngine( void );

#endif
