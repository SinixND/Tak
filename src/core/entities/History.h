#ifndef IG20260308205300
#define IG20260308205300

#include "GameConstants.h"
#include "PlayerAction.h"

/**
 * @brief: Stack to store player turns
 */
typedef struct
{
    /// Stack to store the actions to be undone
    PlayerAction actions[HISTORY_SIZE];
    /// Track index of last action that can be undone
    int lastActionIdx;
    /// Track count of actions that can be redone
    int redoCount;
} History;

#endif
