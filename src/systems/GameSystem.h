#ifndef IG20260222210840
#define IG20260222210840

#include "FileId.h"
#include "Game.h"
#include "RankId.h"

/** 
 * @brief: Return new/clean game object
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
 * @brief: From Board to Player; Undo History
 *
 * - Take one stone from stack/square
 * - Increase reserves
 * - Adjust history index
 */ 
void undoPlaceStone( Game* const pGame );

/** 
 * @brief: From Player to Board; Redo History
 *
 * - Reduce reserves
 * - Put stone on stack/square
 * - Adjust history index
 */ 
void redoPlaceStone( Game* const pGame );

/** 
 * @brief: From Board to Buffer; Add to History
 *
 * - Set stone type of buffer
 * - Loop: Add stones to buffer
 * - Remove stones from square 
 * - Add action to history
 */ 
void pickUpStack(
    Game* const pGame,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY
);

/** 
 * @brief: From Buffer to Board; Undo History
 *
 * - Loop: Add stones to stack/square
 * - Reset buffer
 * - Adjust history index
 */ 
void undoPickUpStack( Game* const pGame );

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

/** 
 * @brief: Undo last action performed by a player
 *
 * - Read history
 * - Switch case and call appropriate function
 * - Adjust history index
 */ 
void undo( Game* const pGame );

/** 
 * @brief: Redo next action performed by a player
 *
 * - Read history
 * - Switch case and call appropriate function
 * - Adjust history index
 */ 
void redo( Game* const pGame );

/// Currently used to avoid unused function warnings
void demo( Game* const pGame );

#endif
