#ifndef IG20251123234852
#define IG20251123234852

#include "GameConstants.h"
#include <stdint.h>

/**
 * @brief Player stats
 */
typedef struct Reserves
{
    /// Current reserves available
    uint8_t regular[PLAYER_COUNT];
    uint8_t capstone[PLAYER_COUNT];
} Reserves;

#endif
