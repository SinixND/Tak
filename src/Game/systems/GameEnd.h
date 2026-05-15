#ifndef IG20260511103855
#define IG20260511103855

#include "FileId.h"
#include "Game.h"
#include "PathSquare.h"
#include "PlayerId.h"
#include "RankId.h"
#include <stdbool.h>

/// Return if provided player satisfies win condition
bool isWinConditionMet(
    Game const* const pGame,
    PlayerId const playerId
);

/// Return if complete road exists
bool checkRoadCondition(
    Board const* const pBoard,
    PlayerId const playerId
);

/// Reset PathSquare array
void resetPathSquares( PathSquare pathSquares[SQUARES_MAX] );

/// Fill pathSquares with valid squares from board
void updatePathSquares(
    PathSquare pathSquares[SQUARES_MAX],
    Board const* const pBoard,
    PlayerId const playerId
);

/// Check if square is valid for path
bool isSquareValid(
    Board const* const pBoard,
    int const squareIdx,
    PlayerId const playerId
);

/// Find path from bottom to top
bool findVerticalRoad(
    PathSquare pathSquares[BOARD_SIZE_MAX * BOARD_SIZE_MAX],
    FileId const fileX,
    RankId const rankY,
    int const boardSize
);

/// Find path from left to right
bool findHorizontalRoad(
    PathSquare pathSquares[BOARD_SIZE_MAX * BOARD_SIZE_MAX],
    FileId const fileX,
    RankId const rankY,
    int const boardSize
);

#endif
