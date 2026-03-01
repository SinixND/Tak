#ifndef IG20260301213022
#define IG20260301213022

#include "PlayerTurn.h"

PlayerAction newPlayerActionPlace(
    int count,
    StoneType stackType,
    FileId file,
    RankId rank,
    DirectionId direction,
    int drops[BOARD_WIDTH_MAX]
);

PlayerAction newPlayerActionMove(
    int count,
    StoneType stackType,
    FileId file,
    RankId rank,
    DirectionId direction,
    int drops[BOARD_WIDTH_MAX]
);

#endif
