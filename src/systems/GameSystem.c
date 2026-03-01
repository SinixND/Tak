#include "GameSystem.h"

#include "BoardSystem.h"
#include "GameConstants.h"
#include "MatchConfigsSystem.h"
#include "PlayerActionsSystem.h"
#include "PlayersSystem.h"
#include "StackBufferSystem.h"
#include "StoneType.h"

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

    return game;
}

