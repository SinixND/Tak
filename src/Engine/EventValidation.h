#ifndef IG20260406164717
#define IG20260406164717

#include "Event.h"
#include "Game.h"
#include <stdbool.h>

/// Validate placement event against game rules
bool validateEventPlace(
    Event const* const pEvent,
    Game const* const pGame
);

/// Validate lift event against game rules
bool validateEventLift(
    Event const* const pEvent,
    Game const* const pGame
);

/// Validate drop event against game rules
bool validateEventDrop(
    Event const* const pEvent,
    Game const* const pGame
);

/// Validate stone type against reserves
bool isStoneTypeAvailable(
    Event const* const pEvent,
    Reserves const* const pReserves
);

/// Validate fileX against board width
bool isFileXOnBoard(
    Event const* const pEvent,
    int const boardWidth
);

/// Validate rankY against board width
bool isRankYOnBoard(
    Event const* const pEvent,
    int const boardWidth
);

/// Validate square against board
bool isSquareEmpty(
    Event const* const pEvent,
    Board const* const pBoard
);

/// Validate playerId against board
bool doesPlayerOwnStack(
    Event const* const pEvent,
    Board const* const pBoard
);

/// Validate drop count against stack buffer
bool isDropCountValid(
    Event const* const pEvent,
    int const stackBufferStoneCount
);

/// Validate dropped stone against (new) captive
bool isCaptiveValid(
    Event const* const pEvent,
    Board const* const pBoard
);

#endif
