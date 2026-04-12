#ifndef IG20260408201348
#define IG20260408201348

#include "ActionTypeId.h"
#include "CommandStateId.h"
#include "DirectionId.h"
#include "FileId.h"
#include "GameConstants.h"
#include "InputBuffer.h"
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
    int8_t dropCounts[BOARD_SIZE_MAX]; // Stone count dropped
    int8_t drops;
} Command;

/// Return initialized player command object
Command newCommand( void );

/// Run state machine to build command from input
void runBuildCommandFSM(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
);

/// Build command from input buffer
void handleStateGetAction(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
);

/// Set action type if input is valid
bool parseInputAction(
    Command* const pCommand,
    InputBuffer const* const pInputBuffer
);

/// Check if event can be build from command
bool isCommandComplete( Command const* const pCommand );

#endif
