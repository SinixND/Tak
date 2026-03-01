#ifndef IG20251203194322
#define IG20251203194322

#include "Game.h"

Game playStone(
    Game game,
    PlayerId const playerId,
    int const positionX,
    int const positionY,
    StoneType const stoneType
);

Game undoPlayStone(
    Game game,
    PlayerId const playerId,
    int const positionX,
    int const positionY,
    StoneType const stoneType
);

#endif
