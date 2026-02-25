#ifndef IG20251123234852
#define IG20251123234852

#include "GameConstants.h"

/**
 * @brief Player stats
 */
typedef struct
{
    /// Stones in play
    int stonesInPlay[PLAYER_COUNT];
    /// Current reserves available
    int regularReserves[PLAYER_COUNT];
    int capstoneReserves[PLAYER_COUNT];
} Players;

#endif
