#ifndef IG20260511103855
#define IG20260511103855

#include "FileId.h"
#include "Game.h"
#include "GameConstants.h"
#include "PathSquare.h"
#include "PlayerId.h"
#include "RankId.h"
#include "Reserves.h"
#include <stdbool.h>

/// Return if provided player satisfies win condition
bool isWinConditionMet(
    Game const* const pGame,
    PlayerId const playerId
);

/// Check if empty places left
bool isBoardFull( Board const* const pBoard );

/// Check remaining reserves w/ respect to board size
bool areReservesExhausted(
    Reserves const* const pReserves,
    int const boardSize
);

/// Return if complete road exists
bool isRoadComplete(
    Board const* const pBoard,
    PlayerId const playerId
);

/// Reset PathSquare array
void resetPathSquares(
    PathSquare pathSquares[SQUARES_MAX],
    int const squareCount
);

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
bool isRoadCompleteVertical(
    PathSquare pathSquares[SQUARES_MAX],
    FileId const fileX,
    RankId const rankY,
    int const boardSize
);

/// Find path from left to right
bool isRoadCompleteHorizontal(
    PathSquare pathSquares[SQUARES_MAX],
    FileId const fileX,
    RankId const rankY,
    int const boardSize
);

#endif
