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

bool validateCommandActionType(
    Command const* const pCommand,
    Game const* const pGame
);

bool validateCommandStoneType(
    Command const* const pCommand,
    Game const* const pGame
);

bool validateCommandFileX(
    Command const* const pCommand,
    Game const* const pGame
);

bool validateCommandRankY(
    Command const* const pCommand,
    Game const* const pGame
);

bool validateCommandDirection(
    Command const* const pCommand,
    Game const* const pGame
);

bool validateCommandDropAmount(
    Command* const pCommand,
    Game const* const pGame
);

#endif
