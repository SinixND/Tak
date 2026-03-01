#ifndef IG20251203194322
#define IG20251203194322

#include "FileId.h"
#include "Game.h"
#include "RankId.h"

Game playStone(
    Game game,
    PlayerId const playerId,
    FileId const column,
    RankId const row,
    StoneType const stoneType
);

Game undoPlayStone(
    Game game,
    PlayerId const playerId,
    FileId const column,
    RankId const row,
    StoneType const stoneType,
    StoneType const captiveType
);

#endif
