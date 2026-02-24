#include "GameSystem.h"

#include "BoardSystem.h"
#include "GameConstants.h"
#include "MatchConfigsSystem.h"
#include "PlacementSystem.h"
#include "PlayersSystem.h"
#include "StackSystem.h"

Game newGame( int boardWidth )
{
    if ( !boardWidth )
    {
        boardWidth = BOARD_WIDTH_DEFAULT;
    }

    Game game = {
        .matchConfigs = getMatchConfigs( boardWidth ),
        .players = newPlayers( boardWidth ),
        .tempStack = newStack(),
        .board = newBoard(),
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
        FLAT
    );

    return game;
}

