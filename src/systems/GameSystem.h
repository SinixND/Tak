#ifndef IG20260222210840
#define IG20260222210840

#include "Game.h"

/// Provide boardWidth 0 for default value
Game newGame( int boardWidth );

Game run( Game game );

Game playStone(
    Game game,
    PlayerId const playerId,
    FileId const file,
    RankId const rank,
    StoneType const stoneType
);

Game undoPlayStone(
    Game game,
    PlayerId const playerId,
    FileId const file,
    RankId const rank,
    StoneType const stoneType,
    StoneType const captiveType
);

// Game undoAction(
//     Game game,
//     PlayerAction const action
// );

#endif
