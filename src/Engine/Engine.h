#ifndef IG20260410152134
#define IG20260410152134

#include "Command.h"
#include "Event.h"
#include "Game.h"
#include "InputBuffer.h"

/**
 * @brief: Build command from input and against game
 *
 * - Parse input
 * - Validate
 */
void buildCommand(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer,
    Game const* const pGame
);

/// Build event from command
void buildEvent(
    Event* const pEvent,
    Command const* const pCommand,
    int const boardSize
);

#endif
