#include "Game.h"

#include "Board.h"
#include "GameConstants.h"
#include "GameSettings.h"
#include "MatchConstants.h"
#include "Players.h"
#include "Stacks.h"
#include "Stones.h"

Game initGame( int boardSize )
{
    if ( !boardSize )
    {
        boardSize = getDefaultSettings().boardSize;
    }

    Game game = {
        //* Adjust settings
        .gameSettings = {
            .boardSize = boardSize
        },
        //* Apply settings
        .matchConstants = defineMatchConstants( game.gameSettings.boardSize ),
        //* Initialize values
        .players = initPlayers( PLAYER_COUNT, game.matchConstants.regularStoneReserves, game.matchConstants.capstoneReserves ),
        .stones = initStones( PLAYER_COUNT, getTotalReserves( game.matchConstants ) ),
        .stacks = initStacks( game.gameSettings.boardSize ),
        .board = initBoard( game.gameSettings.boardSize )
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
