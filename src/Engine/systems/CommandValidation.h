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

/**
* @brief: Check if...
* ... playerId matches game.active player
* ... action type is either `Place` or `Lift`
 */ 
bool validateCommandActionType(
    Command const* const pCommand,
    Game const* const pGame
);

/// Check for sufficient reserves
bool validateCommandStoneType(
    Command const* const pCommand,
    Game const* const pGame
);

/// Check if file is on board
bool validateCommandFileX(
    Command const* const pCommand,
    Game const* const pGame
);

/// Check if rank is on board
bool validateCommandRankY(
    Command const* const pCommand,
    Game const* const pGame
);

/// Check if adjacent field is on board
bool validateCommandDirection(
    Command const* const pCommand,
    Game const* const pGame
);

/// Caps drop count to stackBuffer size if value exceeds size
bool validateCommandDropAmount(
    Command* const pCommand,
    Game const* const pGame
);

#endif
