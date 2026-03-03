#ifndef IG20260222211441
#define IG20260222211441

#include "GameConstants.h"
#include "PlayerId.h"
#include <stdint.h>

/**
 * @brief A stack is a pile of stones
 *
 * The playerId of a stack is determined by the its top stone
 * In terms of code a single stone is a stack of count 1
 *
 * IMPORTANT: Top stone may either be
 * - the last index (regular stack, stones added "on top")
 * - the first index (for stackBuffer, stones appended "to bottom")
 */
typedef struct
{
    /// StoneId is the players Id/color
    PlayerId stoneIds[STONES_MAX];
    /// Count of active stack stones
    uint8_t count : 7;
} Stack;

#endif
