#ifndef IG20251219102623
#define IG20251219102623

#include "FileId.h"
#include "RankId.h"

/// Returns number of square/tile/stack [0, 1, 2, ...]
int positionToSquare(
    FileId const fileX,
    RankId const rankY,
    int const boardWidth
);

/// Returns index of first stone of stack
int squareToStackIndex(
    int const squareIdx,
    int const stackCapacity
);

#endif
