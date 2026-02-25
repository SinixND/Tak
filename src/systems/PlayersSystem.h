#ifndef IG20251221041510
#define IG20251221041510

#include "PlayerId.h"
#include "Players.h"
#include "StoneType.h"

/// Return new Players SoA
Players newPlayers( int const boardWidth );

/// Returns number/index of the stone taken
Players takeFromReserves(
    Players players,
    PlayerId const playerId,
    StoneType const type
);

#endif
