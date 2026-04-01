#ifndef IG20260327195918
#define IG20260327195918

#include "ActionTypeId.h"
#include "FileId.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdint.h>

/**
 * @brief: Store multiple user inputs needed for a complete game event
 */
typedef struct GameEvent
{
    ActionType actionType;
    FileId fileX;
    RankId rankY;
    PlayerId stoneId;
    StoneType stoneType;
    int8_t dropsDone; // Dropping none counts as drop
    int8_t stonesToDrop;
} GameEvent;

#endif
