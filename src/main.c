#include "GameSettings.h"
#include "Players.h"
#include "RuleSystem.h"
#include "RulesData.h"

int main( void )
{
    //* Adjust settings
    GameSettings settings = getDefaultSettings();

    //* Apply settings
    int const INITIAL_REGULAR_STONE_COUNT_PER_PLAYER = getPlayerInitialRegularStoneCount( settings.boardSize );

    int const INITIAL_CAPSTONE_COUNT_PER_PLAYER = getPlayerInitialCapstoneCount( settings.boardSize );

    //* Allocate memory
    Players players = allocatePlayerComponents( PLAYER_COUNT );

    //* Initialize values
    initPlayers(
        &players,
        PLAYER_COUNT,
        INITIAL_REGULAR_STONE_COUNT_PER_PLAYER,
        INITIAL_CAPSTONE_COUNT_PER_PLAYER
    );

    //* Deinitialize data
    deinitPlayers( &players );

    return 0;
}
