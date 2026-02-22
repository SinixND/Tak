#ifndef IG20251219004301
#define IG20251219004301

#include "Stacks.h"
#include "StoneType.h"

/// Return new Stacks SoA
Stacks newStacks( int const boardWidth );

/**
 * @brief: Place stone on top of stack
 *
 * - Set new stone as topStone to stack
 * - Set played stone type
 * - Increase stack height
 */
Stacks putStoneOnStack(
    Stacks stacks,
    int const stackIdx,
    StoneType const type
);

#endif
