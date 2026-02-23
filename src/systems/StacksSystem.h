#ifndef IG20251219004302
#define IG20251219004302

#include "Stacks.h"
#include "StoneType.h"

/// Return new Stacks SoA
Stacks newStacks( int const boardWidth );

/**
 * @brief: Place stone on top of stack
 *
 * - Add stone affiliation
 * - Set played stone type
 * - Increase stack height
 */
Stacks putStoneOnStack(
    Stacks stacks,
    int const stackIdx,
    int const playerIdx,
    StoneType const type
);

#endif
