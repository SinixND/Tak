#ifndef IG20260327195918
#define IG20260327195918

#include "ActionTypeId.h"
#include "FileId.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <stdint.h>

/// User inputs to modify game state
typedef struct Event
{
    ActionType actionType;
    PlayerId playerId;
    StoneType stoneType;
    FileId fileX;
    RankId rankY;
    int8_t dropCount;
} Event;

/// Return initialized game event object
Event newEvent( void );

#endif
