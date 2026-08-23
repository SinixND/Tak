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
bool parseDefaultInputToCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize
);

/// Set action type (place / lift) if input is valid
bool parseActionTypeToCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
);

/// Set stone type if input is valid
bool parseStoneTypeInputToCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
);

/// Set fileX / rankY if input is valid
bool parsePositionInputToCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize
);

/// Set rankY if input is valid
bool parseRankYInputToCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize
);

/// Set dirction if input is valid
bool parseDirectionInputToCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize
);

/// Set first drop amount (0 - n) if input is valid
bool parseFirstDropAmountInputToCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize
);

/// Set drop amount (1 - n) if input is valid
bool parseDropAmountInputToCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize
);

#endif
