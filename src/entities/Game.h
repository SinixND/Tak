#ifndef IG20251205132519
#define IG20251205132519

#include "MatchConfigs.h"
#include "Players.h"
#include "Stack.h"
#include "Stacks.h"

typedef struct
{
    MatchConfigs matchConfigs;
    Players players;
    Stacks board;
    Stack tempStack;
} Game;

#endif
