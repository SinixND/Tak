#ifndef IG20260327200011
#define IG20260327200011

#include "Board.h"
#include "Game.h"
#include "GameEvent.h"
#include "Players.h"
#include "StackBuffer.h"
#include <stdbool.h>

/// Return initialized game event object
GameEvent newGameEvent( void );

/// Validate event against game rules
bool validateEvent(
    GameEvent const* const pEvent,
    Game const* const pGame
);

/// Validate placement event against game rules
bool validateEventPlace(
    GameEvent const* const pEvent,
    Game const* const pGame
);

/// Validate lift event against game rules
bool validateEventLift(
    GameEvent const* const pEvent,
    Game const* const pGame
);

/// Validate drop event against game rules
bool validateEventDrop(
    GameEvent const* const pEvent,
    Game const* const pGame
);

/// Validate stone type against reserves
bool isStoneTypeAvailable(
    GameEvent const* const pEvent,
    Players const* const pPlayers
);

/// Validate fileX against board width
bool isFileXOnBoard(
    GameEvent const* const pEvent,
    int const boardWidth
);

/// Validate rankY against board width
bool isRankYOnBoard(
    GameEvent const* const pEvent,
    int const boardWidth
);

/// Validate square against board
bool isSquareEmpty(
    GameEvent const* const pEvent,
    Board const* const pBoard
);

/// Validate playerId against board
bool doesPlayerOwnStack(
    GameEvent const* const pEvent,
    Board const* const pBoard
);

/// Validate dropped stone against (new) captive
bool isCaptiveValid(
    GameEvent const* const pEvent,
    Board const* const pBoard
);

/// Validate direction offset against board width
bool isOffsetXOnBoard(
    GameEvent const* const pEvent,
    int const boardWidth
);

/// Validate direction offset against board width
bool isOffsetYOnBoard(
    GameEvent const* const pEvent,
    int const boardWidth
);

/// Validate drop count against stack buffer
bool isDropCountValid(
    GameEvent const* const pEvent,
    int const stackBufferStoneCount
);

#endif
