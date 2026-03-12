#ifndef IG20251221041510
#define IG20251221041510

#include "PlayerId.h"
#include "Players.h"
#include "StoneType.h"

/// Return initialized Players object
Players newPlayers( int const boardWidth );

/**
 * @brief: Reduce reserves for given player and stone type
 *
 * - Decrease reserves
 * - Increase stones in play
 */
void takeFromReserves(
    Players* const players,
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
    Players* const players,
    PlayerId const playerId,
    StoneType const stoneType
);

#endif
