#ifndef IG20260308214101
#define IG20260308214101

#include "FileId.h"
#include "History.h"
#include "RankId.h"
#include "StoneType.h"

void recordPlacementAction(
    History* const pHistory,
    StoneType const stoneType,
    FileId const fileX,
    RankId const rankY
);

void undoHistory( History* const pHistory );
void redoHistory( History* const pHistory );

#endif
