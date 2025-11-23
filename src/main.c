#include "GameSettings.h"
#include "PlayerSystem.h"
#include "Players.h"
#include "RuleSystem.h"
#include "RulesData.h"
#include "StoneSystem.h"
#include "Stones.h"
#include <assert.h>

int main( void )
{
    /// Adjust settings
    GameSettings settings = { .boardSize = 5 };

    /// Apply settings
    int const INITIAL_REGULAR_STONE_COUNT_PER_PLAYER =
        getPlayerInitialRegularStoneCount( settings.boardSize );

    int const INITIAL_CAPSTONE_COUNT_PER_PLAYER =
        getPlayerInitialCapstoneCount( settings.boardSize );

    int const INITIAL_STONE_COUNT_PER_PLAYER =
        INITIAL_REGULAR_STONE_COUNT_PER_PLAYER
        + INITIAL_CAPSTONE_COUNT_PER_PLAYER;

    //* Allocate memory
    Players players = allocatePlayerComponents( PLAYER_COUNT );

    Stones stones = allocateStoneComponents(
        PLAYER_COUNT,
        INITIAL_STONE_COUNT_PER_PLAYER
    );

    //* Initialize values
    initPlayers(
        &players,
        PLAYER_COUNT,
        INITIAL_REGULAR_STONE_COUNT_PER_PLAYER,
        INITIAL_CAPSTONE_COUNT_PER_PLAYER
    );

    initStones(
        &stones,
        PLAYER_COUNT,
        INITIAL_STONE_COUNT_PER_PLAYER
    );

    // Stacks board = initBoard(
    //     settings.boardSize
    // );

    /// Deinitialize data
    deinitPlayers( &players );
    deinitStones( &stones );
    // deinitBoard(board);

    return 0;
}
