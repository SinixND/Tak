#ifndef IG20260308205300
#define IG20260308205300

#include "GameConstants.h"
#include "PlayerAction.h"
#include <stdint.h>

/**
 * @brief: Stack to store player turns
 */
typedef struct
{
    /// Stack to store the actions to be undone
    PlayerAction actions[HISTORY_SIZE];
    /// Track index of last action that can be undone
    uint8_t lastActionIdx;
    /// Track count of actions that can be redone
    uint8_t redoCount;
} History;

#endif
