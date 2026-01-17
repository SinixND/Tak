#include "Game.h"

#include "Board.h"
#include "GameConstants.h"
#include "GameSettings.h"
#include "MatchConstants.h"
#include "PlacementSystem.h"
#include "Players.h"
#include "Stacks.h"
#include "StoneType.h"
#include "Stones.h"

Game initGame( int boardWidth )
{
    if ( !boardWidth )
    {
        boardWidth = getDefaultSettings().boardWidth;
    }

    Game game = {
        .gameSettings = { .boardWidth = boardWidth },
        .matchConstants = defineMatchConstants( game.gameSettings.boardWidth ),
        .players = initPlayers(
            PLAYER_COUNT,
            game.matchConstants.regularStoneReserves,
            game.matchConstants.capstoneReserves
        ),
        .stones = initStones(
            PLAYER_COUNT,
            getTotalPlayerReserves( game.matchConstants )
        ),
        .stacks = initStacks( game.gameSettings.boardWidth ),
        .board = initBoard( game.gameSettings.boardWidth )
    };

    return game;
}

// void run( Game* game )
// {
// }

void deinitGame( Game* game )
{
    deinitPlayers( &game->players );
    deinitStones( &game->stones );
    deinitStacks( &game->stacks );
    deinitBoard( &game->board );
}
