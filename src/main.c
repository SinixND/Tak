#include "Board.h"
#include "GameConstants.h"
#include "GameSettings.h"
#include "MatchConstants.h"
#include "Players.h"
#include "Stacks.h"
#include "Stones.h"

int main( void )
{
    //* Adjust settings
    GameSettings gameSettings = getDefaultSettings();

    //* Apply settings
    MatchConstants matchConstants = defineMatchConstants( gameSettings.boardSize );

    //* Initialize values
    Players players = initPlayers(
        PLAYER_COUNT,
        matchConstants.regularStoneReserves,
        matchConstants.capstoneReserves
    );

    Stones stones = initStones(
        PLAYER_COUNT,
        getTotalReserves( matchConstants )
    );

    Stacks stacks = initStacks( gameSettings.boardSize );

    Board board = initBoard( gameSettings.boardSize );

    //* Deinitialize data
    deinitPlayers( &players );
    deinitStones( &stones );
    deinitStacks( &stacks );
    deinitBoard( &board );

    return 0;
}
