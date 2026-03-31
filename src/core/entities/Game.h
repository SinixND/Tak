#ifndef IG20251205132519
#define IG20251205132519

#include "Board.h"
#include "History.h"
#include "PlayerId.h"
#include "Players.h"
#include "StackBuffer.h"

/**
 * @brief: Object to handle game state
 */
typedef struct Game
{
    Board board;
    History history;
    StackBuffer stackBuffer;
    Players players;
    PlayerId activePlayer;
} Game;

#endif
