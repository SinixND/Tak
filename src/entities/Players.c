#include "Players.h"

#include <assert.h>
#include <stdlib.h>

/// Allocate memory; Add one extra to enable invalid ID = 0
Players allocatePlayerComponents( int playerCount );

Players initPlayers(
    int const playerCount,
    int const regularReserves,
    int const capstoneReserves
)
{
    Players players = allocatePlayerComponents( playerCount );

    int idx = 0;

    players.regularReserves[0] = 0;
    players.capstoneReserves[0] = 0;

    for ( int n = 0; n < playerCount; ++n )
    {
        ++idx;

        players.regularReserves[idx] = regularReserves;
        players.capstoneReserves[idx] = capstoneReserves;
    }

    assert(
        players.regularReserves[1] > 0
        && players.capstoneReserves[1] > 0
        && players.regularReserves[2] > 0
        && players.capstoneReserves[2] > 0
        && "Initial player reserves are all >0"
    );

    return players;
}

void deinitPlayers( Players* const players )
{
    free( players->regularReserves );
    free( players->capstoneReserves );
}

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
