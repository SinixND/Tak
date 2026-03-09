#ifndef IG20251221041510
#define IG20251221041510

#include "PlayerId.h"
#include "Players.h"
#include "StoneType.h"

Players newPlayers( int const boardWidth );

void takeFromReserves(
    Players* const players,
    PlayerId const playerId,
    StoneType const type
);

void returnToReserves(
    Players* const players,
    PlayerId const playerId,
    StoneType const type
);

#endif
