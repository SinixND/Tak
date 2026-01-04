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
    assert(
        regularReserves > 0
        && "Invalid regularReserves value"
    );

    assert(
        capstoneReserves > -1
        && "Invalid capstoneReserves value"
    );

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
    assert(
        playerCount > 0
        && "Invalid playerCount"
    );

    Players players = { .count = playerCount };

    players.regularReserves = calloc( playerCount, sizeof( int ) );
    assert( players.regularReserves && "Bad allocation" );

    players.capstoneReserves = calloc( playerCount, sizeof( int ) );
    assert( players.capstoneReserves && "Bad allocation" );

    return players;
}
