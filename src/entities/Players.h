#ifndef IG20251123234852
#define IG20251123234852

#include "GameConstants.h"
#include <stdint.h>

/**
 * @brief Player stats
 */
typedef struct
{
    /// Stones in play
    uint8_t stonesInPlay[PLAYER_COUNT];
    /// Current reserves available
    uint8_t reservesRegular[PLAYER_COUNT];
    uint8_t reservesCapstone[PLAYER_COUNT];
} Players;

#endif
