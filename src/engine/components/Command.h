#ifndef IG20260408201348
#define IG20260408201348

#include "ActionTypeId.h"
#include "DirectionId.h"
#include "FileId.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <stdint.h>

/// Multi-frame player command to build a game event
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

/// Check if event can be build from command
bool isCommandComplete( Command const* const command );

#endif
