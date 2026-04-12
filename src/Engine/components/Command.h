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
void runBuildCommandFSM( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Choose what game event to prepare
void handleStateGetAction( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Get stone type
void handleStateGetStoneType( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Get column of target square
void handleStateGetFileX( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Get row of target square
void handleStateGetRankY( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Get direction to move stack
void handleStateGetDirection( Command* const pCommand, InputBuffer const* const pInputBuffer );

// /// Get drop count (can be 0 on initial square)
void handleStateGetFirstDropAmount( Command* const pCommand, InputBuffer const* const pInputBuffer );

// /// Get drop count
void handleStateGetDropAmount( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Set action type (place / lift) if input is valid
bool parseInputAction( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Set stone type if input is valid
bool parseInputStoneType( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Set fileX if input is valid
bool parseInputFileX( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Set rankY if input is valid
bool parseInputRankY( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Set dirction if input is valid
bool parseInputDirection( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Set first drop amount (0 - n) if input is valid
bool parseInputFirstDropAmount( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Set drop amount (1 - n) if input is valid
bool parseInputDropAmount( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Check if event can be build from command
bool isCommandComplete( Command const* const pCommand );

#endif
