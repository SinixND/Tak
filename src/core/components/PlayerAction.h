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
 * Inputs: Position, StoneCount
 *
 * Action: Drop
 * Inputs: Position, Captive
 *
 */
typedef struct PlayerAction
{
    ActionType actionType; // P, L, D
    PlayerId playerId;     // White or black
    uint8_t squareIdx;     // Square
    uint8_t topStoneIdx;   // Top stone of stack
    StoneType stoneType;   // F, S, C
    uint8_t stoneCount;    // Max: board width
    bool flattened;        // Capstone flattened standing
} PlayerAction;

#endif
