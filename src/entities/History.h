#ifndef IG20260308205300
#define IG20260308205300

#include "GameConstants.h"
#include "PlayerAction.h"

typedef struct
{
    PlayerAction undoActions[HISTORY_SIZE];
    PlayerAction redoActions[HISTORY_SIZE];
    int undoCount;
    int redoCount;
} History;

#endif
