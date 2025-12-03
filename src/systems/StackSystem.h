#ifndef IG20251219004301
#define IG20251219004301

#include "Stacks.h"
#include "StoneType.h"
#include "Stones.h"

int getStackIdx(
    int* const boardStackIdxs,
    int* const stacksOnBoardCount,
    int const position
);

void putStoneOnStack(
    Stones* const stones,
    Stacks* const stacks,
    int const stoneIdx,
    int const stackIdx,
    StoneType const type
);

#endif
