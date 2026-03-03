#include "GameSystem.h"

#include "BoardSystem.h"
#include "FileId.h"
#include "GameConstants.h"
#include "MatchConfigsSystem.h"
#include "PlayerId.h"
#include "PlayersSystem.h"
#include "PositionSystem.h"
#include "RankId.h"
#include "StackBufferSystem.h"
#include "StoneType.h"
#include <assert.h>

Game newGame( int boardWidth )
{
    if ( !boardWidth )
    {
        boardWidth = BOARD_WIDTH_DEFAULT;
    }

    Game game = {
        .board = newBoard(),
        .stackBuffer = newStackBuffer(),
        .players = newPlayers( boardWidth ),
        .matchConfigs = getMatchConfigs( boardWidth ),
    };

    return game;
}

Game run( Game game )
{
    game = placeStone(
        game,
        PLAYER_WHITE,
        0,
        0,
        STONE_TYPE_FLAT
    );

    return game;
}

Game placeStone(
    Game game,
    PlayerId const playerId,
    FileId const file,
    RankId const rank,
    StoneType const stoneType
)
{
    int const stackIdx = positionToStackIndex(
        file,
        rank,
        game.matchConfigs.boardWidth
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

    game.board = placeStoneOnBoard(
        game.board,
        stackIdx,
        playerId,
        stoneType
    );

    return game;
}

