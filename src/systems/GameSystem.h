#ifndef IG20260222210840
#define IG20260222210840

#include "FileId.h"
#include "Game.h"
#include "RankId.h"

/// Provide boardWidth 0 for default value
Game newGame( int boardWidth );

Game run( Game game );

Game placeStone(
    Game game,
    PlayerId const playerId,
    FileId const file,
    RankId const rank,
    StoneType const stoneType
);

#endif
