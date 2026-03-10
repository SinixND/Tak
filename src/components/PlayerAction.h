#ifndef IG20260301185150
#define IG20260301185150

#include "DirectionId.h"
#include "FileId.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneType.h"
#include <stdint.h>

/**
 * @brief: PTN (Portable Tak Notion) object
 * Place: (stoneType)(file)(rank)
 * Move: (count)(file)(rank)(direction)(drops)(stoneType)(*)(')(')
 *
 * Merged: (playerId)(stoneType)(count)(file)(rank)(direction)(drops)(flattened)(Tak)(Tinuë)
 *
 * To differantiate placement from moves: Placments have count == 0
 * Tak == road threat; Tinuë == Guaranteed win next turn
 */
typedef struct
{
    PlayerId playerId;     // White or black
    StoneType stoneType;   // F, S, C
    uint8_t count;         // 0 for placement
    FileId fileX;          // Square: Column
    RankId rankY;          // Square: Row
    DirectionId direction; // right, left, up, down
    // uint8_t tak;           // Bool: Road threat?
    // uint8_t tinue;         // Bool: Unavoidable road threat?
    uint8_t drops[BOARD_WIDTH_MAX]; // Consecutive drops including starting square
    uint8_t flattend;               // Bool: Flattened a standing stone/wall?
} PlayerAction;

//* Alternative struct
// typedef struct
// {
//     uint8_t drops[BOARD_WIDTH_MAX];
//     uint8_t count : 4;         // 0 for placement
//     FileId fileX : 3;          // Square: Column
//     RankId rankY : 3;          // Square: Row
//     PlayerId playerId : 2;     // White or black
//     StoneType stoneType : 2;   // F, S, C
//     DirectionId direction : 2; // right, left, up, down
//     uint8_t flattend : 1;      // Bool: Flattened a standing stone/wall?
//     uint8_t tak : 1;           // Bool: Road threat?
//     uint8_t tinue : 1;         // Bool: Unavoidable road threat?
// } PlayerAction;

#endif
