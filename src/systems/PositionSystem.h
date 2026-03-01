#ifndef IG20251219102623
#define IG20251219102623

#include "BoardWidthId.h"
#include "FileId.h"
#include "RankId.h"

int positionToBoardIndex(
    FileId const column,
    RankId const row,
    BoardWidthId const boardWidthId
);

#endif
