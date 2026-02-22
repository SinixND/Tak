#ifndef IG20251123234345
#define IG20251123234345

#include "GameConstants.h"
#include "StoneType.h"

/**
 * @brief A stack is a pile of stones
 *
 * The affiliation of a stack is determined by the its top stone
 * Only the top stone of a stack can have a type other than `FLAT`
 * In terms of code a single stone is a stack of height 1
 * The board is represented by its stacks.
 */
typedef struct
{
    /// Types of stacks / top stones
    StoneType types[STACKS_ARRAY_SIZE];
    /// Heights of stacks
    int heights[STACKS_ARRAY_SIZE];
    /// Stone affiliations
    int affiliations[STACKS_ARRAY_SIZE][STONES_MAX];
} Stacks;

#endif
