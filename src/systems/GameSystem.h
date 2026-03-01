#ifndef IG20260222210840
#define IG20260222210840

#include "Game.h"

/// Provide boardWidth 0 for default value
Game newGame( BoardWidthId boardWidthId );

Game run( Game game );

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
