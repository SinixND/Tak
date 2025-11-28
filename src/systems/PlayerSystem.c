#include "PlayerSystem.h"

#include "Players.h"
#include "RulesData.h"
#include <assert.h>
#include <stdlib.h>

Players allocatePlayerComponents( int playerCount )
{
    Players players;

    players.regularReserves = malloc( 1 + playerCount * sizeof( int ) );
    assert( players.regularReserves && "Bad malloc" );

    players.capstoneReserves = malloc( playerCount * sizeof( int ) );
    assert( players.capstoneReserves && "Bad malloc" );

    return players;
}

void initPlayers(
    Players* players,
    int const playerCount,
    int const regularReserves,
    int const capstoneReserves
)
{
    players->regularReserves[0] = 0;
    players->capstoneReserves[0] = 0;

    int idx = 1;

    for ( int n = 0; n < playerCount; ++n )
    {
        players->regularReserves[idx] = regularReserves;
        players->capstoneReserves[idx] = capstoneReserves;

        ++idx;
    }
}

void deinitPlayers( Players* const players )
{
    free( players->regularReserves );
    free( players->capstoneReserves );
}
