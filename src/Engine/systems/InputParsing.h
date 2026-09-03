#ifndef IG20260414225052
#define IG20260414225052

#include "Command.h"
#include "InputBuffer.h"
#include "UIData.h"
#include <stdbool.h>

/// Parse input into command
bool updateCommandFromInput(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize,
    UIData const* const pUIData
);

/// Set stone type or file
bool parseDefaultInputToCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize,
    UIData const* const pUIData
);

/// Set fileX / rankY if input is valid
bool parsePositionInputToCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize,
    UIData const* const pUIData
);

/// Set dirction if input is valid
bool parseDirectionInputToCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize,
    UIData const* const pUIData
);

/// Set first drop amount (0 - n) if input is valid
bool parseFirstDropAmountInputToCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize,
    UIData const* const pUIData
);

/// Set drop amount (1 - n) if input is valid
bool parseDropAmountInputToCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    int const boardSize,
    UIData const* const pUIData
);

#endif
