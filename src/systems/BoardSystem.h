#ifndef IG20251219004302
#define IG20251219004302

#include "Board.h"
#include "FileId.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneType.h"

Board newBoard( int const boardWidth );

Board placeStoneOnBoard(
    Board board,
    FileId const fileX,
    RankId const rankY,
    PlayerId const playerId,
    StoneType const stoneType
);

#endif
