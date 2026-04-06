#ifndef IG20260406175208
#define IG20260406175208

#include "App.h"

/**
 * @brief: Undo last action performed by a player
 *
 * - Read history
 * - Change game state
 * - Adjust history index
 */
void undo( App* const pApp );

/// From Board to Player
void undoPlaceStone( App* const pApp );

/// From Buffer to Board
void undoLiftStack( App* const pApp );

/// From Board to Buffer
void undoDropStone( App* const pApp );

#endif
