#ifndef IG20260308214101
#define IG20260308214101

#include "History.h"
#include "StoneTypeId.h"

/// Return initialized history object
History newHistory( void );

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
    int const squareIdx,
    StoneType const stoneType
);

/**
 * @brief: Add lift action to history
 *
 * - Increase history index
 * - Reset redo count
 * - Add player action with lift input
 */
void recordLiftAction(
    History* const pHistory,
    int const squareIdx,
    int const topStoneIdx,
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
void recordDropAction(
    History* const pHistory,
    PlayerId const playerId,
    int const squareIdx,
    StoneType const stoneType,
    bool const flattened
);

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
