#include "GameSystem.h"

#include "GameConstants.h"
#include "MatchConfigsSystem.h"
#include "PlacementSystem.h"
#include "PlayerSystem.h"
#include "StacksSystem.h"

Game newGame( int boardWidth )
{
    if ( !boardWidth )
    {
        boardWidth = BOARD_WIDTH_DEFAULT;
    }

    Game game = {
        .matchConfigs = getMatchConfigs( boardWidth ),
        .players = newPlayers( boardWidth ),
        .board = newStacks( boardWidth ),
    };

    return game;
}

Game run( Game game )
{
    placeStoneOnBoard(
        game,
        0,
        0,
        0,
        FLAT
    );

    return game;
}

