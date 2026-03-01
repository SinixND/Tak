#include "GameSystem.h"

#include "BoardSystem.h"
#include "DirectionId.h"
#include "FileId.h"
#include "GameConstants.h"
#include "MatchConfigsSystem.h"
#include "PlayerActionSystem.h"
#include "PlayerTurn.h"
#include "PlayersSystem.h"
#include "PositionSystem.h"
#include "RankId.h"
#include "StackBufferSystem.h"
#include "StoneType.h"
#include <assert.h>

Game newGame( BoardWidthId boardWidthId )
{
    if ( !boardWidthId )
    {
        boardWidthId = BOARD_WIDTH_DEFAULT;
    }

    Game game = {
        .board = newBoard(),
        .stackBuffer = newStackBuffer(),
        .players = newPlayers( boardWidthId ),
        .matchConfigs = getMatchConfigs( boardWidthId ),
    };

    return game;
}

Game run( Game game )
{
    game = playStone(
        game,
        PLAYER_WHITE,
        0,
        0,
        STONE_TYPE_FLAT
    );

    game = undoPlayStone(
        game,
        PLAYER_WHITE,
        0,
        0,
        STONE_TYPE_FLAT,
        STONE_TYPE_NONE
    );

    // game.undoStack[0] = newPlayerActionMove(
    //     1,
    //     STONE_TYPE_FLAT,
    //     FILE_A,
    //     RANK_1,
    //     DIR_RIGHT,
    //     1,
    //     (int[8]){ 1, 0, 0, 0, 0, 0, 0, 0 }
    // );

    return game;
}

Game playStone(
    Game game,
    PlayerId const playerId,
    FileId const file,
    RankId const rank,
    StoneType const stoneType
)
{
    int const stackIdx = positionToBoardIndex(
        file,
        rank,
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

    game.undoStack[game.undoStackSize] = newPlayerActionPlace(
        stoneType,
        file,
        rank
    );

    ++game.undoStackSize;

    return game;
}

Game undoPlayStone(
    Game game,
    PlayerId const playerId,
    FileId const file,
    RankId const rank,
    StoneType const stoneType,
    StoneType const captiveType
)
{
    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    int const stackIdx = positionToBoardIndex(
        file,
        rank,
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

// Game undoAction(
//     Game game,
//     PlayerAction const action
// )
// {
//     // //* !Count == placement
//     // if ( game.undoStack[game.undoStackSize - 1].count )
//     // {
//     //     //* TODO: undoMove
//     // }
//     // else
//     // {
//     //     undoPlayStone(
//     //         game,
//     //
//     //     )
//     // }
// }

