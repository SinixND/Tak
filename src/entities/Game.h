#ifndef IG20251205132519
#define IG20251205132519

#include "Board.h"
#include "History.h"
#include "Players.h"
#include "StackBuffer.h"

typedef struct
{
    Board board;
    History history;
    StackBuffer stackBuffer;
    Players players;
} Game;

#endif
