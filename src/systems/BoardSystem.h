#ifndef IG20251219004302
#define IG20251219004302

#include "Board.h"
#include "PlayerId.h"
#include "StoneType.h"

Board newBoard( int const boardWidth );

void pushOntoStack(
    Board* const pBoard,
    int const squareIdx,
    PlayerId const playerId
);

void placeStoneOnBoard(
    Board* const pBoard,
    int const squareIdx,
    PlayerId const playerId,
    StoneType const stoneType
);

#endif
