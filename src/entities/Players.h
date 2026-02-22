#ifndef IG20251123234852
#define IG20251123234852

#include "GameConstants.h"

/**
 * @brief Player stats
 */
typedef struct
{
    /// Stones in play
    int stonesInPlay[PLAYER_COUNT + 1];
    /// Current reserves available
    int regularReserves[PLAYER_COUNT + 1];
    int capstoneReserves[PLAYER_COUNT + 1];
} Players;

#endif
