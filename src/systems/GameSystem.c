#include "GameSystem.h"

#include "BoardSystem.h"
#include "GameConstants.h"
#include "MatchConfigsSystem.h"
#include "PlacementSystem.h"
#include "PlayersSystem.h"
#include "StackBufferSystem.h"
#include "StoneType.h"

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
    game = placeStoneOnBoard(
        game,
        1,
        0,
        0,
        STONE_TYPE_FLAT
    );

    return game;
}

