#ifndef IG20260222210840
#define IG20260222210840

#include "FileId.h"
#include "Game.h"
#include "RankId.h"

/// Provide boardWidth 0 for default value
Game newGame( int boardWidth );

void placeStone(
    Game* const pGame,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY,
    StoneType const stoneType
);

void pickUpStack(
    Game* const pGame,
    FileId const fileX,
    RankId const rankY
);

//* NOTE: Dont forget to implement this (first undo drops from PlayerAction-Info) then drop all on origin?
// void abortMove( Game* const pGame );

void dropStone(
    Game* const pGame,
    FileId const fileX,
    RankId const rankY
);

void demo( Game* const pGame );

#endif
