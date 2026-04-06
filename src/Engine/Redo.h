#ifndef IG20260406175030
#define IG20260406175030

#include "App.h"

/**
 * @brief: Redo next action performed by a player
 *
 * - Read history
 * - Change game state
 * - Adjust history index
 */
void redo( App* const pApp );

/// From Player to Board; Redo History
void redoPlaceStone( App* const pApp );

/// From Board to Buffer; Redo History
void redoLiftStack( App* const pApp );

/// From Buffer to Board
void redoDropStone( App* const pApp );

#endif
