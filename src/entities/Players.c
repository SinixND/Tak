#include "Players.h"

#include <assert.h>
#include <stdlib.h>

/// Allocate memory
Players allocatePlayerComponents( int playerCount );

Players initPlayers(
    int const playerCount,
    int const regularReserves,
    int const capstoneReserves
)
{
    Players players = allocatePlayerComponents( playerCount );

    for ( int idx = 0; idx < playerCount; ++idx )
    {
        players.regularReserves[idx] = regularReserves;
        players.capstoneReserves[idx] = capstoneReserves;
    }

    return players;
}

void deinitPlayers( Players* const players )
{
    free( players->regularReserves );
    free( players->capstoneReserves );
}

Players allocatePlayerComponents( int playerCount )
{
    Players players;

    players.regularReserves = malloc( playerCount * sizeof( int ) );
    assert( players.regularReserves && "Bad malloc" );

    players.capstoneReserves = malloc( playerCount * sizeof( int ) );
    assert( players.capstoneReserves && "Bad malloc" );

    return players;
}
