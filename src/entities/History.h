#ifndef IG20260308205300
#define IG20260308205300

#include "GameConstants.h"
#include "PlayerAction.h"

typedef struct
{
    PlayerAction undo[HISTORY_SIZE];
    PlayerAction redo[HISTORY_SIZE];
} History;

#endif
