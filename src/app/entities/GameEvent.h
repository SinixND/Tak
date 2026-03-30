#ifndef IG20260327195918
#define IG20260327195918

#include "ActionTypeId.h"
#include "DirectionId.h"
#include "FileId.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdint.h>

/**
 * @brief: Store multiple user inputs needed for a complete game event
 */
typedef struct
{
    PlayerId stoneId;
    ActionType actionType;
    StoneType stoneType;
    FileId fileX;
    RankId rankY;
    DirectionId direction;
    int8_t dropCounts[BOARD_WIDTH_MAX];
    int8_t dropCountsSize;
    int8_t droppedCount;
} GameEvent;

#endif
