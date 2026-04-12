#ifndef IG20260412020914
#define IG20260412020914

#include "Command.h"
#include "InputBuffer.h"

/// Run application state machine
void runBuildCommandFSM(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
);

/// Build command from input buffer
void handleStateGetAction(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
);

#endif
