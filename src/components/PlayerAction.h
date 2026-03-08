#ifndef IG20260301185150
#define IG20260301185150

#include "DirectionId.h"
#include "FileId.h"
#include "GameConstants.h"
#include "RankId.h"
#include "StoneType.h"
#include <stdint.h>

/**
 * @brief: PTN (Portable Tak Notion) object
 * Place: (stone)(square)
 * Move: (count)(square)(direction)(drops)(stone)(*)(')(')
 * Merged: (count)(stone)(square)(direction)(drops)(flattened)(Tak)(Tinuë)
 *
 * To differantiate placement from moves: Placments have count == 0
 * Tak == road threat; Tinuë == Guaranteed win next turn
 */
typedef struct
{
    uint8_t count : 4;         // 0 for placement
    StoneType stoneType : 2;   // F, S, C
    FileId fileX : 3;          // Square: Column
    RankId rankY : 3;          // Square: Row
    DirectionId direction : 2; // right, left, up, down
    uint8_t flattend : 1;      // Bool: Flattened a standing stone/wall?
    // uint8_t tak : 1;           // Bool: Road threat?
    // uint8_t tinue : 1;         // Bool: Unavoidable road threat?
    uint8_t drops[BOARD_WIDTH_MAX];
} PlayerAction;

#endif
