#ifndef IG20260301185150
#define IG20260301185150

#include "ActionTypeId.h"
#include "FileId.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief: Action to be stored in history to enable undo/redo
 *
 * Action: Placement
 * Inputs: PlayerId, Position, StoneType
 *
 * Action: Lift
 * Inputs: Position
 *
 * Action: Drop
 * Inputs: Position, StoneCount, flattened
 *
 */
typedef struct HistoryRecord
{
    PlayerId playerId;     // White or black
    ActionType actionType; // P, L, D
    FileId fileX;          // A-H
    RankId rankY;          // 1-8
    StoneType stoneType;   // F, S, C
    uint8_t stoneCount;    // Max: board width
    bool flattened;        // Capstone flattened standing
} HistoryRecord;

#endif
