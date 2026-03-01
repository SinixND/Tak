#include "PlayerActionSystem.h"

#include "PlayerTurn.h"

PlayerAction newPlayerActionPlace(
    StoneType const stoneType,
    FileId const file,
    RankId const rank
)
{
    PlayerAction action = {
        .count = 0,
        .stoneType = stoneType,
        .file = file,
        .rank = rank,
        .direction = DIR_UP,
        .flattend = 0,
        .drops = { 0 },
    };

    return action;
}

// PlayerAction newPlayerActionMove(
//     int const count,
//     StoneType const stoneType,
//     FileId const file,
//     RankId const rank,
//     DirectionId const direction,
//     int const flattened,
//     int const* const drops
// )
// {
//     PlayerAction action = {
//         .count = count,
//         .stoneType = stoneType,
//         .file = file,
//         .rank = rank,
//         .direction = direction,
//         .flattend = flattened,
//         .drops = { 0 }
//     };
//
//     for ( int idx = 0; idx < BOARD_WIDTH_MAX; ++idx )
//     {
//         action.drops[idx] = drops[idx];
//     }
//
//     return action;
// }

