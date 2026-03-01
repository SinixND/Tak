#ifndef IG20251203194322
#define IG20251203194322

#include "ColumnId.h"
#include "Game.h"
#include "RowId.h"

Game playStone(
    Game game,
    PlayerId const playerId,
    ColumnId const column,
    RowId const row,
    StoneType const stoneType
);

Game undoPlayStone(
    Game game,
    PlayerId const playerId,
    ColumnId const column,
    RowId const row,
    StoneType const stoneType,
    StoneType const captiveType
);

#endif
