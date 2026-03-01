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
 * Move: (count)(square)(direction)(drops)(stone)
 * Merged: (count)(stone)(square)(direction)(drops)
 * To differantiate placement from moves: Placments have count == 0
 */
typedef struct
{
    uint8_t count : 4;         // 0 for placement
    StoneType stackType : 2;   // F, S, C
    FileId file : 3;           // Square: Column
    RankId rank : 3;           // Square: Row
    DirectionId direction : 2; // right, left, up, down
    uint8_t drops[BOARD_WIDTH_MAX];
} PlayerAction;

#endif
