#ifndef IG20260415110428
#define IG20260415110428

#include "Command.h"
#include "Event.h"

/// Build event from command
void buildEvent(
    Event* const pEvent,
    Command const* const pCommand,
    int const boardSize
);

#endif
