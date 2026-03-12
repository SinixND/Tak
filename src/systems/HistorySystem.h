#ifndef IG20260308214101
#define IG20260308214101

#include "FileId.h"
#include "History.h"
#include "RankId.h"
#include "StoneType.h"

/** 
 * @brief: Add placement action to history
 *
 * - Increase history index
 * - Reset redo count
 * - Add player action with placement input
 */ 
void recordPlacementAction(
    History* const pHistory,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY,
    StoneType const stoneType
);

/** 
 * @brief: Add pickup action to history
 *
 * - Increase history index
 * - Reset redo count
 * - Add player action with pickup input
 */ 
void recordPickUpAction(
    History* const pHistory,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY,
    StoneType const stoneType,
    int const stoneCount
);

/** 
 * @brief: Add drop action to history
 *
 * - Increase history index
 * - Reset redo count
 * - Add player action with drop input
 */ 
// void recordDropAction(
//     History* const pHistory,
//     FileId const fileX,
//     RankId const rankY
// );

/** 
 * @brief: Adjust history index and counter
 *
 * - Decrease history index
 * - Increase redo count
 */ 
void undoHistory( History* const pHistory );

/** 
 * @brief: Adjust history index and counter
 *
 * - Increase history index
 * - Decrease redo count
 */ 
void redoHistory( History* const pHistory );

#endif
