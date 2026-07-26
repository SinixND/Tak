#ifndef IG20260414225052
#define IG20260414225052

#include "Command.h"
#include "Game.h"
#include "InputBuffer.h"
#include <stdbool.h>

/// Parse input into command
bool parseInput(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    Game const* const pGame
);

/// Set stone type or file
bool parseInputFirst(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
);

/// Set action type (place / lift) if input is valid
bool parseInputActionType(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
);

/// Set stone type if input is valid
bool parseInputStoneType(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
);

/// Set fileX if input is valid
bool parseInputFileX(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
);

/// Set rankY if input is valid
bool parseInputRankY(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    Game const* const pGame
);

/// Set dirction if input is valid
bool parseInputDirection(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
);

/// Set first drop amount (0 - n) if input is valid
bool parseInputFirstDropAmount(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
);

/// Set drop amount (1 - n) if input is valid
bool parseInputDropAmount(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
);

#endif
