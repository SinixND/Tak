#ifndef IG20260222210840
#define IG20260222210840

#include "FileId.h"
#include "Game.h"
#include "RankId.h"

/// Provide boardWidth 0 for default value
Game newGame( int boardWidth );

/// From Player to Board; Add to History
void placeStone(
    Game* const pGame,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY,
    StoneType const stoneType
);

/// From Board to Player; Undo History
void undoPlaceStone( Game* const pGame );

/// From Player to Board; Redo History
void redoPlaceStone( Game* const pGame );

/// From Board to Buffer; Add to History
void pickUpStack(
    Game* const pGame,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY
);

/// From Buffer to Board; Undo History
void undoPickUpStack( Game* const pGame );

/// From Buffer to Board
void dropStone(
    Game* const pGame,
    FileId const fileX,
    RankId const rankY
);

void undo( Game* const pGame );

void redo( Game* const pGame );

void demo( Game* const pGame );

//* NOTE: Dont forget to implement this (first undo drops from PlayerAction-Info) then drop all on origin?
// void abortMove( Game* const pGame );

#endif
