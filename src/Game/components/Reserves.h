#ifndef IG20251123234852
#define IG20251123234852

#include "GameConstants.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <stdint.h>

/**
 * @brief Player stone reserves
 */
typedef struct Reserves
{
    /// Current reserves available
    uint8_t regular[PLAYER_COUNT];
    uint8_t capstone[PLAYER_COUNT];
} Reserves;

/// Return initialized object
Reserves newReserves( int const boardSize );

/**
 * @brief Reduce reserves for given player and stone type
 *
 * - Decrease reserves
 * - Increase stones in play
 */
void takeFromReserves(
    Reserves* const pReserves,
    PlayerId const playerId,
    StoneType const stoneType
);

/**
 * @brief Increase reserves for given player and stone type
 *
 * - Increase reserves
 * - Decrease stones in play
 */
void returnToReserves(
    Reserves* const pReserves,
    PlayerId const playerId,
    StoneType const stoneType
);

#endif
