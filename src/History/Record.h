#ifndef IG20260301185150
#define IG20260301185150

#include "ActionTypeId.h"
#include "PlayerId.h"
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
typedef struct Record
{
    ActionType actionType; // P, L, D
    PlayerId playerId;     // White or black
    uint8_t squareIdx;     // File & Rank
    StoneType stoneType;   // F, S, C
    bool flattened;        // Capstone flattened standing
} Record;

#endif
