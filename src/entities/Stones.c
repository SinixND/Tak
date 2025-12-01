#include "Stones.h"

#include <assert.h>
#include <stdlib.h>

Stones allocateStoneComponents( int const stoneCount )
{
    int const maxIdx = stoneCount + 1;

    Stones stones;

    stones.affiliations = malloc( maxIdx * sizeof( int ) );
    assert( stones.affiliations && "Bad malloc" );

    stones.captives = malloc( maxIdx * sizeof( int ) );
    assert( stones.captives && "Bad malloc" );

    return stones;
}

void initStones(
    Stones* stones,
    int const playerCount,
    int const stoneCountPerPlayer
)
{
    int playerId = 0;
    int idx = 0;

    stones->affiliations[idx] = playerId;
    stones->captives[idx] = 0;

    for ( int n = 0; n < playerCount; ++n )
    {
        ++playerId;

        for ( int m = 0; m < stoneCountPerPlayer; ++m )
        {
            ++idx;

            stones->affiliations[idx] = playerId;
            stones->captives[idx] = 0;
        }
    }

    assert(
        stones->affiliations[0] == 0
        && stones->captives[0] == 0
        && "StoneId 0 is unassigned"
    );

    assert(
        stones->affiliations[1] == 1
        && stones->affiliations[stoneCountPerPlayer] == 1
        && "Stone [1] to [n]: Affiliation is (player) 1"
    );

    assert(
        stones->affiliations[stoneCountPerPlayer + 1] == 2
        && stones->affiliations[2 * stoneCountPerPlayer] == 2
        && "Stone [n+1] to [2*n]: Affiliation is (player) 2"
    );
}

void deinitStones( Stones* const stones )
{
    free( stones->affiliations );
    free( stones->captives );
}
