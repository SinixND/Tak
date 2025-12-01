#include "Players.h"

#include <assert.h>
#include <stdlib.h>

Players allocatePlayerComponents( int playerCount )
{
    int const maxIdx = playerCount + 1;

    Players players;

    players.regularReserves = malloc( maxIdx * sizeof( int ) );
    assert( players.regularReserves && "Bad malloc" );

    players.capstoneReserves = malloc( maxIdx * sizeof( int ) );
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
    int idx = 0;

    players->regularReserves[0] = 0;
    players->capstoneReserves[0] = 0;

    for ( int n = 0; n < playerCount; ++n )
    {
        ++idx;

        players->regularReserves[idx] = regularReserves;
        players->capstoneReserves[idx] = capstoneReserves;
    }

    assert(
        players->regularReserves[1] > 0
        && players->capstoneReserves[1] > 0
        && players->regularReserves[2] > 0
        && players->capstoneReserves[2] > 0
        && "Initial player reserves are all >0"
    );
}

void deinitPlayers( Players* const players )
{
    free( players->regularReserves );
    free( players->capstoneReserves );
}
