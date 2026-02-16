#ifndef IG20251219004301
#define IG20251219004301

#include "Stacks.h"
#include "StoneType.h"
#include "Stones.h"

/**
 * @brief Return (and create if necessary) stackIdx at board index
 */
int createOrGetStackIdx(
    int* const boardStackIdxs,
    int* const stacksOnBoardCount,
    int* const stackBoardIdxs,
    int const boardIdx
);

void putStoneOnStack(
    Stones* const stones,
    Stacks* const stacks,
    int const stoneIdx,
    int const stackIdx,
    StoneType const type
);

#endif
