#ifndef IG20251219004302
#define IG20251219004302

#include "Board.h"
#include "PlayerId.h"
#include "StoneType.h"

Board newBoard( void );

Board addStoneToBoard(
    Board board,
    int const stackIdx,
    PlayerId const playerId,
    StoneType const stoneType
);
);

#endif
