#ifndef IG20260414225300
#define IG20260414225300

#include "Command.h"
#include "Game.h"
#include <stdbool.h>

/// Validate if command is valid against game
bool validateCommand(
    Command* const pCommand,
    Game const* const pGame
);

bool validateInputActionType(
    Command* const pCommand,
    Game const* const pGame
);

bool validateInputStoneType(
    Command* const pCommand,
    Game const* const pGame
);

bool validateInputFileX(
    Command* const pCommand,
    Game const* const pGame
);

bool validateInputRankY(
    Command* const pCommand,
    Game const* const pGame
);

bool validateInputDirection(
    Command* const pCommand,
    Game const* const pGame
);

bool validateInputFirstDropAmount(
    Command* const pCommand,
    Game const* const pGame
);

bool validateInputDropAmount(
    Command* const pCommand,
    Game const* const pGame
);

#endif
