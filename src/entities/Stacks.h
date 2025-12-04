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
    /// Stacks on the board
    int onBoardCount;
    /// Indexes of top stone
    int* topStoneIdxs;
    /// Heights of stacks including top stone
    int* heights;
    /// Types of stacks / top stones
    StoneType* types;
} Stacks;

/// Allocate memory and initialize values
Stacks initStacks( int const boardSize );

/// Free allocated memory
void deinitStacks( Stacks* const stacks );

#endif
