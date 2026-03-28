#ifndef IG20260327200011
#define IG20260327200011

#include "Board.h"
#include "Game.h"
#include "GameEvent.h"
#include "Players.h"
#include <stdbool.h>

/// Return initialized game event object
GameEvent newGameEvent( void );

/// Validate event against game rules
bool validateEvent(
    GameEvent const* const event,
    Game const* const game
);

/// Validate placement event against game rules
bool validateEventPlace(
    GameEvent const* const event,
    Game const* const game
);

/// Validate lift event against game rules
bool validateEventLift(
    GameEvent const* const event,
    Game const* const game
);

/// Validate drop event against game rules
bool validateEventDrop(
    GameEvent const* const event,
    Game const* const game
);

/// Validate stone type against reserves
bool isStoneTypeAvailable(
    GameEvent const* const event,
    Players const* const players
);

/// Validate fileX against board width
bool isFileXOnBoard(
    GameEvent const* const event,
    int const boardWidth
);

/// Validate rankY against board width
bool isRankYOnBoard(
    GameEvent const* const event,
    int const boardWidth
);

/// Validate square against board
bool isSquareEmpty(
    GameEvent const* const event,
    Board const* const board
);

/// Validate playerId against board
bool doesPlayerOwnStack(
    GameEvent const* const event,
    Board const* const board
);

/// Validate dropped stone against (new) captive
bool isCaptiveValid(
    GameEvent const* const event,
    Board const* const board
);

/// Validate direction offset against board width
bool isOffsetXOnBoard(
    GameEvent const* const event,
    int const boardWidth
);

/// Validate direction offset against board width
bool isOffsetYOnBoard(
    GameEvent const* const event,
    int const boardWidth
);

#endif
