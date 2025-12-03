#include "Stones.h"

#include <assert.h>
#include <stdlib.h>

/// Allocate memory; Add one extra to enable invalid ID = 0
Stones allocateStoneComponents( int const stoneCount );

Stones initStones(
    int const playerCount,
    int const stoneCountPerPlayer
)
{
    Stones stones = allocateStoneComponents( playerCount * stoneCountPerPlayer );

    int const maxIdx = ( playerCount * stoneCountPerPlayer ) + 1;

    for ( int idx = 0; idx < maxIdx; ++idx )
    {
        stones.affiliations[idx] = 0;
        stones.captives[idx] = 0;
    }

    return stones;
}

void deinitStones( Stones* const stones )
{
    free( stones->affiliations );
    free( stones->captives );
}

Stones allocateStoneComponents( int const stoneCount )
{
    int const maxIdx = stoneCount + 1;

    Stones stones = { .inPlay = 0 };

    stones.affiliations = malloc( maxIdx * sizeof( int ) );
    assert( stones.affiliations && "Bad malloc" );

    stones.captives = malloc( maxIdx * sizeof( int ) );
    assert( stones.captives && "Bad malloc" );

    return stones;
}

