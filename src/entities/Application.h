#ifndef IG20260315164753
#define IG20260315164753

#include "Game.h"
#include "GameEvent.h"
#include <stdbool.h>

/**
 * @brief: Object to provide the user-game-interface
 *
 * Also responsible for calling backends
 */
typedef struct
{
    /// GameEvent to store user inputs for be processed for game
    GameEvent gameEvent;

    /// Game state
    Game game;

    /// Stop application main loop
    bool appShouldClose;
} Application;

#endif
