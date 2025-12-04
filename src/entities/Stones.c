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
        stones.affiliationIdxs[idx] = -1;
        stones.captiveIdxs[idx] = -1;
    }

    return stones;
}

void deinitStones( Stones* const stones )
{
    free( stones->affiliationIdxs );
    free( stones->captiveIdxs );
}

Stones allocateStoneComponents( int const stoneCount )
{
    Stones stones = { .inPlayCount = 0 };

    stones.affiliationIdxs = malloc( stoneCount * sizeof( int ) );
    assert( stones.affiliationIdxs && "Bad malloc" );

    stones.captiveIdxs = malloc( stoneCount * sizeof( int ) );
    assert( stones.captiveIdxs && "Bad malloc" );

    return stones;
}
