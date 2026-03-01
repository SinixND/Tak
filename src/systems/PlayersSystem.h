#ifndef IG20251221041510
#define IG20251221041510

#include "BoardWidthId.h"
#include "PlayerId.h"
#include "Players.h"
#include "StoneType.h"

Players newPlayers( BoardWidthId const boardWidthId );

Players takeFromReserves(
    Players players,
    PlayerId const playerId,
    StoneType const type
);

Players undoTakeFromReserves(
    Players players,
    PlayerId const playerId,
    StoneType const type
);

#endif
