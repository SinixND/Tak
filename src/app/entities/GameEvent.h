#ifndef IG20260327195918
#define IG20260327195918

#include "ActionTypeId.h"
#include "DirectionId.h"
#include "FileId.h"
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
    DirectionId direction; // Offset is dir * dropsDone
    int8_t dropsDone;      // Dropping none counts as drop
    int8_t stonesToDrop;
} GameEvent;

#endif
