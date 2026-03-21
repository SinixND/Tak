#ifndef IG20260315154123
#define IG20260315154123

#include "ActionType.h"
#include "DirectionId.h"
#include "FileId.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneType.h"
#include <stdint.h>

/**
 * @brief: Store multiple user inputs needed for a complete PlayerAction
 */
typedef struct
{
    PlayerId stonePlayerId;
    ActionType actionType;
    FileId fileX;
    RankId rankY;
    StoneType stoneType;
    DirectionId direction;
    int8_t liftCount;
    int8_t droppedCount;
    int8_t dropCounts[BOARD_WIDTH_MAX];
    int8_t dropsDone;
} GameEvent;

#endif
