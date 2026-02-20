#include "Game.h"

#include "Board.h"
#include "GameConstants.h"
#include "GameSettings.h"
#include "MatchConfigs.h"
#include "PlacementSystem.h"
#include "Players.h"
#include "Stacks.h"
#include "Stones.h"

Game initGame( int boardWidth )
{
    if ( !boardWidth )
    {
        boardWidth = getDefaultSettings().boardWidth;
    }

    Game game = {
        .gameSettings = { .boardWidth = boardWidth },
        .matchConfigs = defineMatchConfigs( game.gameSettings.boardWidth ),
        .players = initPlayers(
            PLAYER_COUNT,
            game.matchConfigs.regularStoneReserves,
            game.matchConfigs.capstoneReserves
        ),
        .stones = initStones(
            PLAYER_COUNT,
            getTotalPlayerReserves( game.matchConfigs )
        ),
        .stacks = initStacks( game.gameSettings.boardWidth ),
        .board = initBoard( game.gameSettings.boardWidth )
    };

    return game;
}

void run( Game* game )
{
    placeStoneOnBoard(
        &game->players,
        &game->board,
        &game->stacks,
        &game->stones,
        0,
        0,
        0,
        FLAT
    );
}

void deinitGame( Game* game )
{
    deinitPlayers( &game->players );
    deinitStones( &game->stones );
    deinitStacks( &game->stacks );
    deinitBoard( &game->board );
}
