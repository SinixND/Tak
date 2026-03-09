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
    PlayerAction undoActions[HISTORY_SIZE];
    /// Track next action index to be undone
    int lastActionIdx;
} History;

#endif
