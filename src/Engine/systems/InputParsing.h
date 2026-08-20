#ifndef IG20260414225052
#define IG20260414225052

#include "Command.h"
#include "InputBuffer.h"
#include <stdbool.h>

/// Parse input into command
bool updateCommandFromInput(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize
);

/// Set stone type or file
bool parseInputFirst(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize
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
    InputBuffer const* const pInputBuffer,
    int const boardSize
);

/// Set rankY if input is valid
bool parseInputRankY(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize
);

/// Set dirction if input is valid
bool parseInputDirection(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize
);

/// Set first drop amount (0 - n) if input is valid
bool parseInputFirstDropAmount(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize
);

/// Set drop amount (1 - n) if input is valid
bool parseInputDropAmount(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize
);

#endif
