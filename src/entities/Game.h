#ifndef IG20251205132519
#define IG20251205132519

#include "Board.h"
#include "MatchConfigs.h"
#include "Players.h"
#include "Stack.h"

typedef struct
{
    MatchConfigs matchConfigs;
    Players players;
    Stack tempStack;
    Board board;
} Game;

#endif
