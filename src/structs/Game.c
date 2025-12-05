#include "Game.h"

#include "Board.h"
#include "GameConstants.h"
#include "GameSettings.h"
#include "MatchConstants.h"
#include "Players.h"
#include "Stacks.h"
#include "Stones.h"

Game initGame(){
    Game game;

    //* Adjust settings
    game.gameSettings = getDefaultSettings();

    //* Gamely settings
    game.matchConstants = defineMatchConstants( gameSettings.boardSize );

    //* Initialize values
    game.players = initPlayers(
        PLAYER_COUNT,
        matchConstants.regularStoneReserves,
        matchConstants.capstoneReserves
    );

    game.stones = initStones(
        PLAYER_COUNT,
        getTotalReserves( matchConstants )
    );

    game.stacks = initStacks( gameSettings.boardSize );

    game.board = initBoard( gameSettings.boardSize );

    return game;
}

Game run(){
}

void deinitGame(Game* game){
    deinitPlayers( &game->players );
    deinitStones( &game->stones );
    deinitStacks( &game->stacks );
    deinitBoard( &game->board );
}