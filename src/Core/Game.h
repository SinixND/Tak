#ifndef IG20251205132519
#define IG20251205132519

#include "Board.h"
#include "Reserves.h"
#include "StackBuffer.h"

/// Object to handle game state
typedef struct Game
{
    Board board;
    StackBuffer stackBuffer;
    Reserves reserves;
} Game;

#endif
