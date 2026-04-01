#ifndef IG20251219102623
#define IG20251219102623

#include "FileId.h"
#include "RankId.h"

/// Return square index for given file/rank
int positionToSquare(
    FileId const fileX,
    RankId const rankY,
    int const boardWidth
);

/// Returns index of first stone of stack for given square index
int squareToStackIndex(
    int const squareIdx,
    int const stackCapacity
);

#endif
