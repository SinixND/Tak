#ifndef IG20251123234345
#define IG20251123234345

#include "GameConstants.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <stdint.h>

/**
 * @brief A board consists of squares/tiles with stacks of stones
 *
 * The owner playerId of a stack is determined by the its top stone
 * Only the top stone of a stack can have a type other than `FLAT`
 * In terms of code a single stone is a stack of count 1
 */
typedef struct Board
{
    /// StoneId is the players Id/color;
    /// Takes stone/stack index
    PlayerId stoneIds[SQUARES_MAX * STONES_MAX];
    /// Active stone counts per stack;
    /// Used to determine status!;
    /// Takes square index
    uint8_t stoneCounts[SQUARES_MAX];
    /// Types of stacks / top stones
    /// Takes square index
    StoneType stackTypes[SQUARES_MAX];
    /// Board squares per side (rank/row and file/column)
    uint8_t size;
    /// Max size of stacks
    uint8_t stackCapacity;
} Board;

/// Return initialized board object
Board newBoard( int const boardSize );

/**
 * @brief; Add new stone to a square
 *
 * - Set stack type
 * - Add playerId to stones
 * - Increase stack count
 */
void putOntoStack(
    Board* const pBoard,
    PlayerId const playerId,
    int const squareIdx,
    StoneType const stoneType
);

/**
 * @brief; Remove n stones from a square
 *
 * - Decrease stack count
 * - Set stack type
 */
void takeFromStack(
    Board* const pBoard,
    int const squareIdx,
    int const stoneCount
);

#endif
