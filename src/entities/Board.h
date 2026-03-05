#ifndef IG20251123234345
#define IG20251123234345

#include "GameConstants.h"
#include "PlayerId.h"
#include "StoneType.h"
#include <stdint.h>

/**
 * @brief A board consists of squares/tiles with stacks of stones
 *
 * The owner playerId of a stack is determined by the its top stone
 * Only the top stone of a stack can have a type other than `FLAT`
 * In terms of code a single stone is a stack of count 1
 */
typedef struct
{
    /// StoneId is the players Id/color;
    /// Takes stone/stack index
    PlayerId stoneIds[SQUARES_MAX * STONES_MAX];
    /// Active stone counts per stack;
    /// Takes square index
    uint8_t counts[SQUARES_MAX];
    /// Types of stacks / top stones
    /// Takes square index
    StoneType types[SQUARES_MAX];

    /// Board squares per side (rank/row and file/column)
    uint8_t width;
    /// Max size of stacks
    uint8_t stackCapacity;
} Board;

#endif
