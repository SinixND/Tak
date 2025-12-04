#include "Stones.h"

#include <assert.h>
#include <stdlib.h>

/// Allocate memory
Stones allocateStoneComponents( int const stoneCount );

Stones initStones(
    int const playerCount,
    int const stoneCountPerPlayer
)
{
    int const stoneCount = playerCount * stoneCountPerPlayer;

    Stones stones = allocateStoneComponents( stoneCount );

    for ( int idx = 0; idx < stoneCount; ++idx )
    {
        stones.affiliations[idx] = -1;
        stones.captives[idx] = -1;
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
    Stones stones = { .inPlay = 0 };

    stones.affiliations = malloc( stoneCount * sizeof( int ) );
    assert( stones.affiliations && "Bad malloc" );

    stones.captives = malloc( stoneCount * sizeof( int ) );
    assert( stones.captives && "Bad malloc" );

    return stones;
}

