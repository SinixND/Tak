#ifndef IG20260308214101
#define IG20260308214101

#include "FileId.h"
#include "History.h"
#include "RankId.h"
#include "StoneType.h"

void recordPlacementAction(
    History* const pHistory,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY,
    StoneType const stoneType
);

void recordPickUpAction(
    History* const pHistory,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY,
    StoneType const stoneType,
    int const stoneCount
);

// void recordDropAction(
//     History* const pHistory,
//     FileId const fileX,
//     RankId const rankY
// );

void undoHistory( History* const pHistory );
void redoHistory( History* const pHistory );

#endif
