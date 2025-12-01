#ifndef IG20251123234345
#define IG20251123234345

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
    /// Id of top stone
    int* topStoneIds;
    /// Height of stack including top stone
    int* heights;
    /// Type of the stack / top stone
    StoneType* types;
} Stacks;

/// Allocate memory; Add one extra to enable invalid ID = 0
Stacks allocateStackComponents( int const boardSize );

/// Initialize values; Leaves [0] uninitialized
void initStacks(
    Stacks* stacks,
    int const boardSize
);

/// Free allocated memory
void deinitStacks( Stacks* const stacks );

#endif
