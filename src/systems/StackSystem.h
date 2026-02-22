#ifndef IG20251219004301
#define IG20251219004301

#include "Stacks.h"
#include "StoneType.h"

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
