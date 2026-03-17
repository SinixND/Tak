#ifndef IG20251205132519
#define IG20251205132519

#include "Board.h"
#include "History.h"
#include "Players.h"
#include "StackBuffer.h"

/**
 * @brief: Object to handle game state
 */
typedef struct
{
    Board board;
    History history;
    StackBuffer stackBuffer;
    Players players;
} Game;

#endif
