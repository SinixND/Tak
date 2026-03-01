#ifndef IG20260301213022
#define IG20260301213022

#include "PlayerTurn.h"

PlayerAction newPlayerActionPlace(
    StoneType const stoneType,
    FileId const file,
    RankId const rank
);

// PlayerAction newPlayerActionMove(
//     int const count,
//     StoneType const stoneType,
//     FileId const file,
//     RankId const rank,
//     DirectionId const direction,
//     int const flattened,
//     int const* const drops
// );

#endif
