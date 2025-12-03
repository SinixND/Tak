#include "Board.h"
#include "GameSettings.h"
#include "Players.h"
#include "RuleSystem.h"
#include "RulesData.h"
#include "Stacks.h"
#include "Stones.h"

int main( void )
{
    //* Adjust settings
    GameSettings settings = getDefaultSettings();

    //* Apply settings
    int const INITIAL_REGULAR_STONE_COUNT_PER_PLAYER = getPlayerInitialRegularStoneCount( settings.boardSize );

    int const INITIAL_CAPSTONE_COUNT_PER_PLAYER = getPlayerInitialCapstoneCount( settings.boardSize );

    int const INITIAL_STONE_COUNT_PER_PLAYER = INITIAL_REGULAR_STONE_COUNT_PER_PLAYER + INITIAL_CAPSTONE_COUNT_PER_PLAYER;

    //* Initialize values
    Players players = initPlayers(
        PLAYER_COUNT,
        INITIAL_REGULAR_STONE_COUNT_PER_PLAYER,
        INITIAL_CAPSTONE_COUNT_PER_PLAYER
    );

    Stones stones = initStones(
        PLAYER_COUNT,
        INITIAL_STONE_COUNT_PER_PLAYER
    );

    Stacks stacks = initStacks( settings.boardSize );

    Board board = initBoard( settings.boardSize );

    //* Deinitialize data
    deinitPlayers( &players );
    deinitStones( &stones );
    deinitStacks( &stacks );
    deinitBoard( &board );

    return 0;
}
