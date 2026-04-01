#ifndef IG20251221041510
#define IG20251221041510

#include "PlayerId.h"
#include "Reserves.h"
#include "StoneTypeId.h"

/// Return initialized Reserves object
Reserves newReserves( int const boardWidth );

/**
 * @brief: Reduce reserves for given player and stone type
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
 * @brief: Increase reserves for given player and stone type
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
