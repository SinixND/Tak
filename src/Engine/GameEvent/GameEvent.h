#ifndef IG20260327195918
#define IG20260327195918

#include "ActionTypeId.h"
#include "FileId.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief: Store multiple user inputs needed for a complete game event
 */
typedef struct GameEvent
{
    ActionType actionType;
    PlayerId stoneId;
    StoneType stoneType;
    FileId fileX;
    RankId rankY;
    int8_t dropCount;
    bool flattened;
} GameEvent;

#endif
