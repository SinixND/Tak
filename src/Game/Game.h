#ifndef IG20251205132519
#define IG20251205132519

#include "Board.h"
#include "FileId.h"
#include "RankId.h"
#include "Reserves.h"
#include "StackBuffer.h"

/// Object to handle game state
typedef struct Game
{
    Board board;
    StackBuffer stackBuffer;
    Reserves reserves;
} Game;

/**
 * @brief: Return initialized game object
 *
 * - Provide boardWidth 0 for default value
 */
Game newGame( int boardWidth );

/**
 * @brief: From Player to Board; Add to history
 *
 * - Reduce reserves
 * - Put stone on stack/square
 * - Add action to history
 */
void placeStone(
    Game* const pGame,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY,
    StoneType const stoneType
);

/**
 * @brief: From Board to Buffer; Add to History
 *
 * - Set stone type of buffer
 * - Loop: Add stones to buffer
 * - Remove stones from square
 * - Add action to history
 */
void liftStack(
    Game* const pGame,
    FileId const fileX,
    RankId const rankY
);

/**
 * @brief: From Buffer to Board
 *
 * - Add single stone to stack/square
 * - Remove single stone from buffer
 */
void dropStone(
    Game* const pGame,
    FileId const fileX,
    RankId const rankY
);

#endif
