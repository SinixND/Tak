#ifndef IG20251219004302
#define IG20251219004302

#include "Board.h"
#include "PlayerId.h"
#include "StoneType.h"

Board newBoard( int const boardWidth );

void putOntoStack(
    Board* const pBoard,
    int const squareIdx,
    PlayerId const playerId,
    StoneType const stoneType
);

void takeFromStack(
    Board* const pBoard,
    int const squareIdx,
    int const stoneCount
);

#endif
