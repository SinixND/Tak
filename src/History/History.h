#ifndef IG20260308205300
#define IG20260308205300

#include "FileId.h"
#include "GameConstants.h"
#include "HistoryRecord.h"
#include "RankId.h"
#include <stdint.h>

/// Stack to store player actions
typedef struct History
{
    /// Stack to store the records to be undone
    HistoryRecord records[HISTORY_SIZE];
    /// Track index of last record that can be undone
    int16_t lastRecordIdx;
    /// Track count of records that can be redone
    uint16_t redoCount;
} History;

/// Return initialized history object
History newHistory( void );

/**
 * @brief: Add placement action to history
 *
 * - Increase history index
 * - Reset redo count
 * - Add player action with placement input
 */
void recordActionPlacement(
    History* const pHistory,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY,
    StoneType const stoneType
);

/**
 * @brief: Add lift action to history
 *
 * - Increase history index
 * - Reset redo count
 * - Add player action with lift input
 */
void recordActionLift(
    History* const pHistory,
    FileId const fileX,
    RankId const rankY
);

/**
 * @brief: Add drop action to history
 *
 * - Increase history index
 * - Reset redo count
 * - Add player action with drop input
 */
void recordActionDrop(
    History* const pHistory,
    PlayerId const playerId,
    FileId const fileX,
    RankId const rankY,
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
