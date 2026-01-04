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
    assert(
        playerCount > 0
        && "Invalid playerCount"
    );

    assert(
        stoneCountPerPlayer > 0
        && "Invalid stoneCountPerPlayer"
    );

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
    assert(
        stoneCount > 0
        && "Invalid stoneCount"
    );

    Stones stones = { .inPlayCount = 0 };

    stones.affiliationIdxs = calloc( stoneCount, sizeof( int ) );
    assert( stones.affiliationIdxs && "Bad allocation" );

    stones.captiveIdxs = calloc( stoneCount, sizeof( int ) );
    assert( stones.captiveIdxs && "Bad allocation" );

    return stones;
}
