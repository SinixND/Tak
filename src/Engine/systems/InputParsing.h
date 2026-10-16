#ifndef IG20260414225052
#define IG20260414225052

#include "App.h"
#include "Command.h"
#include "Input.h"
#include "UI.h"
#include <stdbool.h>

/// Handle input that directly changes app state
void handleGlobalInput( App* const pApp );

/// Parse input into command
bool updateCommandFromInput(
    Command* const pCommand,
    Input const* const pInput,
    int const boardSize,
    UI const* const pUI
);

/// Set stone type or file
bool parseDefaultInputToCommand(
    Command* const pCommand,
    Input const* const pInput,
    int const boardSize,
    UI const* const pUI
);

/// Set fileX / rankY if input is valid
bool parsePositionInputToCommand(
    Command* const pCommand,
    Input const* const pInput,
    int const boardSize,
    UI const* const pUI
);

/// Set dirction if input is valid
bool parseDirectionInputToCommand(
    Command* const pCommand,
    Input const* const pInput,
    int const boardSize,
    UI const* const pUI
);

/// Set first drop amount (0 - n) if input is valid
bool parseFirstDropAmountInputToCommand(
    Command* const pCommand,
    Input const* const pInput,
    int const boardSize,
    UI const* const pUI
);

/// Set drop amount (1 - n) if input is valid
bool parseDropAmountInputToCommand(
    Command* const pCommand,
    Input const* const pInput,
    int const boardSize,
    UI const* const pUI
);

#endif
