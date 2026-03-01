#include "PlayerActionsSystem.h"

#include "BoardSystem.h"
#include "FileId.h"
#include "PlayerId.h"
#include "PlayersSystem.h"
#include "PositionSystem.h"
#include "RankId.h"
#include "StoneType.h"
#include <assert.h>

Game playStone(
    Game game,
    PlayerId const playerId,
    FileId const column,
    RankId const row,
    StoneType const stoneType
)
{
    int const stackIdx = positionToBoardIndex(
        column,
        row,
        game.matchConfigs.boardWidthId
    );

    //* Rule: Can only place on empty squares
    assert(
        game.board.stacks[stackIdx].count == 0
        && "Can only place on empty square"
    );

    assert(
        game.board.types[stackIdx] == STONE_TYPE_NONE
        && "Can only place on empty square"
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
    FileId const column,
    RankId const row,
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
        game.board.stacks[stackIdx].count > 0
        && "Can only undo from stack with count > 0"
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

