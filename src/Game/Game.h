#ifndef IG20251205132519
#define IG20251205132519

#include "Board.h"
#include "Event.h"
#include "PlayerId.h"
#include "Reserves.h"
#include "StackBuffer.h"
#include <stdbool.h>

/// Object to handle game state
typedef struct Game
{
    Board board;
    StackBuffer stackBuffer;
    Reserves reserves;
    PlayerId activePlayer;
} Game;

/**
 * @brief: Return initialized game object
 *
 * - Provide boardSize 0 for default value
 */
Game newGame( int boardSize );

/**
 * @brief: From Reserves to Board
 *
 * - Reduce reserves
 * - Put stone on stack/square
 */
void placeStone(
    Game* const pGame,
    PlayerId const playerId,
    int const squareIdx,
    StoneType const stoneType
);

/**
 * @brief: From Board to Reserves
 *
 * - Increase reserves
 * - Take stone from stack/square
 */
void takeStone(
    Game* const pGame,
    int const squareIdx
);

/**
 * @brief: From Board to Buffer
 *
 * - Set stone type of buffer
 * - Loop: Add stones to buffer
 * - Remove stones from square
 */
void liftStack(
    Game* const pGame,
    int const squareIdx
);

/**
 * @brief: From Buffer to Board
 *
 * - Undo lift stack
 * - Loop: Add stones to stack
 * - Remove stones from buffer
 */
void dropStack(
    Game* const pGame,
    int const squareIdx
);

/**
 * @brief: From Buffer to Board
 *
 * - Add single stone to stack/square
 * - Remove single stone from buffer
 */
void dropStone(
    Game* const pGame,
    int const squareIdx
);

/**
 * @brief: From Board to Buffer
 *
 * - Undo drop stone
 * - Add single stone to Buffer
 * - Remove single stone from stack
 */
void liftStone(
    Game* const pGame,
    int const squareIdx,
    bool const flattened
);

/// Update game state with event
void executeEvent(
    Game* const pGame,
    Event const* const pEvent
);

#endif
