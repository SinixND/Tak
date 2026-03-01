#ifndef IG20251219102623
#define IG20251219102623

#include "BoardWidthId.h"
#include "ColumnId.h"
#include "RowId.h"

int positionToBoardIndex(
    ColumnId const column,
    RowId const row,
    BoardWidthId const boardWidthId
);

#endif
