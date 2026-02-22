#ifndef IG20251123234852
#define IG20251123234852

#include "GameConstants.h"

/**
 * @brief Player stats
 */
typedef struct
{
    /// Stones in play
    int stonesInPlay[PLAYER_ARRAY_SIZE];
    /// Current reserves available
    int regularReserves[PLAYER_ARRAY_SIZE];
    int capstoneReserves[PLAYER_ARRAY_SIZE];
} Players;

#endif
