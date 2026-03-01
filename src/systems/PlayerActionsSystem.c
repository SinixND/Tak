#include "PlayerActionsSystem.h"

#include "BoardSystem.h"
#include "ColumnId.h"
#include "PlayerId.h"
#include "PlayersSystem.h"
#include "PositionSystem.h"
#include "RowId.h"
#include "StoneType.h"
#include <assert.h>

Game playStone(
    Game game,
    PlayerId const playerId,
    ColumnId const column,
    RowId const row,
    StoneType const stoneType
)
{
    int const stackIdx = positionToBoardIndex(
        column,
        row,
        game.matchConfigs.boardWidthId
    );

    //* Rule: Can only place on empty tiles
    assert(
        game.board.stacks[stackIdx].height == 0
        && "Can only place on empty tile"
    );

    assert(
        game.board.types[stackIdx] == STONE_TYPE_NONE
        && "Can only place on empty tile"
    );

    game.players = takeFromReserves(
        game.players,
        playerId,
        stoneType
    );

    game.board = addStoneToBoard(
        game.board,
        stackIdx,
        playerId,
        stoneType
    );

    return game;
}

Game undoPlayStone(
    Game game,
    PlayerId const playerId,
    ColumnId const column,
    RowId const row,
    StoneType const stoneType,
    StoneType const captiveType
)
{
    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    int const stackIdx = positionToBoardIndex(
        column,
        row,
        game.matchConfigs.boardWidthId
    );

    //* Can it be removed?
    assert(
        game.board.stacks[stackIdx].height > 0
        && "Can only undo from stack with height > 0"
    );

    assert(
        game.board.types[stackIdx] != STONE_TYPE_NONE
        && "Can only undo from stack with type != NONE"
    );

    game.board = undoAddStoneToBoard(
        game.board,
        stackIdx,
        captiveType
    );

    game.players = undoTakeFromReserves(
        game.players,
        playerId,
        stoneType
    );

    return game;
}

