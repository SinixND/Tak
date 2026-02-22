#ifndef IG20251123234345
#define IG20251123234345

#include "GameConstants.h"
#include "StoneType.h"

/**
 * @brief A stack is a pile of stones
 *
 * A stacks affiliation is determined by the its top stone
 * Only the top stone of a stack can have a type other than `FLAT`
 * In terms of code a single stone is a stack of height 1
 */
typedef struct
{
    /// Types of stacks / top stones
    StoneType type;
    /// Height of active stack stones (= valid affiliations)
    int height;
    /// Stone affiliations
    int affiliations[STONES_MAX + 1];
} Stack;

/// Set default values for Stack
Stack initStack( int const boardWidth );

#endif
