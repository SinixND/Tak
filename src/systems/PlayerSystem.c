#include "PlayerSystem.h"

#include "Players.h"
#include "RulesData.h"
#include <assert.h>
#include <stdlib.h>

Players allocatePlayerComponents( int playerCount )
{
    Players players;

    players.regularReserves = malloc( playerCount * sizeof( int ) );
    players.capstoneReserves = malloc( playerCount * sizeof( int ) );

    return players;
}

void initPlayers(
    Players* players,
    int const playerCount,
    int const regularReserves,
    int const capstoneReserves
)
{
    for ( int n = 0; n < playerCount; ++n )
    {
        players.regularReserves[n] = regularReserves;
        players.capstoneReserves[n] = capstoneReserves;
    }
}

void deinitPlayers( Players* const players )
{
    free( players->regularReserves );
    free( players->capstoneReserves );
}
