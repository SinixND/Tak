#include "Game.h"

#include "GameConstants.h"
#include "MatchConfigs.h"
#include "PlacementSystem.h"

Game initGame( int boardWidth )
{
    if ( !boardWidth )
    {
        boardWidth = BOARD_WIDTH_DEFAULT;
    }

    Game game = {
        .matchConfigs = defineMatchConfigs( boardWidth ),
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
