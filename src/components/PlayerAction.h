#ifndef IG20260301185150
#define IG20260301185150

#include "FileId.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneType.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief: Action to be stored in history to enable undo/redo
 *
 * Action: Placement
 * Inputs: PlayerId, Position, StoneType
 *
 * Action: PickUp
 * Inputs: Position, StoneCount
 *
 * Action: Drop
 * Inputs: Position, Captive
 *
 */
typedef struct
{
    PlayerId playerId;   // White or black
    FileId fileX;        // Square: Column
    RankId rankY;        // Square: Row
    StoneType stoneType; // F, S, C
    uint8_t stoneCount;  // Max: board width
    bool flattened;      // Capstone flattened standing
} PlayerAction;

#endif
