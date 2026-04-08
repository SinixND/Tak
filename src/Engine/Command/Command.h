#ifndef IG20260408201348
#define IG20260408201348

#include "ActionTypeId.h"
#include "DirectionId.h"
#include "FileId.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdint.h>

typedef struct Command
{
    PlayerId playerId;
    ActionType actionType;
    StoneType stoneType;
    FileId fileX;
    RankId rankY;
    DirectionId direction;
    int8_t dropCounts[BOARD_WIDTH_MAX]; // Stone count dropped
    int8_t drops;
} Command;

/// Return initialized player command object
Command newCommand( void );

#endif
