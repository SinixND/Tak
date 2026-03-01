#ifndef IG20251205132519
#define IG20251205132519

#include "Board.h"
#include "GameConstants.h"
#include "MatchConfigs.h"
#include "PlayerTurn.h"
#include "Players.h"
#include "StackBuffer.h"

typedef struct
{
    Board board;
    PlayerAction undoStack[HISTORY_SIZE];
    PlayerAction redoStack[HISTORY_SIZE];
    StackBuffer stackBuffer;
    Players players;
    MatchConfigs matchConfigs;
    uint8_t undoStackSize;
    uint8_t redoStackSize;
} Game;

#endif
