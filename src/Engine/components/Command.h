#ifndef IG20260408201348
#define IG20260408201348

#include "ActionTypeId.h"
#include "CommandStateId.h"
#include "DirectionId.h"
#include "FileId.h"
#include "Game.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <stdint.h>

/// Multi-frame player command to build a game event
typedef struct Command
{
    CommandStateId state;
    PlayerId playerId;
    ActionType actionType;
    StoneType stoneType;
    FileId fileX;
    RankId rankY;
    DirectionId direction;
    /// Stone counts dropped
    int8_t dropCounts[BOARD_SIZE_MAX];
    /// Updated post event execution
    int8_t drops;
} Command;

/// Return initialized object
Command newCommand( PlayerId const playerId );

/// Tick command state machine
void setNextCommandState(
    Command* const pCommand,
    Game const* const pGame
);

/// Check if event can be build from command
bool isCommandReady( Command const* const pCommand );

/// Prepare command for next frame after event
void updateCommandPostEvent( Command* const pCommand );

/// Prepare command for next turn
void prepareCommand(
    Command* const pCommand,
    PlayerId const playerId
);

#endif
