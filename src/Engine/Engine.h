#ifndef IG20260410152134
#define IG20260410152134

#include "Command.h"
#include "Event.h"
#include "Game.h"
#include "History.h"
#include "InputBuffer.h"
#include <stdbool.h>

/**
 * @brief Autocomplete drop command if certain conditions are met
 *
 * Returns true if command was autocompleted
 */
bool autocompleteCommand(
    Command* const pCommand,
    Game const* const pGame
);

/**
 * @brief Build command from input and against game
 *
 * - Parse input to command
 * - Validate command
 * - Advance commnd state
 */
void buildCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    Game const* const pGame
);

/// Make history entry from command
void recordCommand(
    History* const pHistory,
    Command const* const pCommand,
    Game const* const pGame
);

/// Build event from command
void buildEvent(
    Event* const pEvent,
    Command const* const pCommand,
    int const boardSize
);

/// Make history entry from event
void recordEvent(
    History* const pHistory,
    Event const* const pEvent,
    Game const* const pGame
);

/// Undo last events
void undoTurn(
    History* const pHistory,
    Game* const pGame
);

/// Redo next events
void redoTurn(
    History* const pHistory,
    Game* const pGame
);

/// Undo events of current turn
void resetTurn(
    Command* const pCommand,
    History* const pHistory,
    Game* const pGame
);

#endif
