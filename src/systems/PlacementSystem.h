#ifndef IG20251203194322
#define IG20251203194322

#include "Board.h"
#include "Players.h"
#include "Stacks.h"
#include "Stones.h"

void placeStoneOnBoard(
    Players* players,
    Board* board,
    Stacks* stacks,
    Stones* stones,
    int const player,
    int const positionX,
    int const positionY,
    StoneType const type
);

#endif
