#ifndef IG20251221041510
#define IG20251221041510

#include "PlayerId.h"
#include "Players.h"
#include "StoneType.h"

Players newPlayers( int const boardWidth );

Players takeFromReserves(
    Players players,
    PlayerId const playerId,
    StoneType const type
);

#endif
