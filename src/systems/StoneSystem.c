#include "StoneSystem.h"

#include "Stones.h"
#include <assert.h>
#include <stdlib.h>

Stones allocateStoneComponents( int const stoneCount )
{
    Stones stones;

    stones.affiliations = malloc( ( 1 + stoneCount ) * sizeof( int ) );
    assert( stones.affiliations && "Bad malloc" );

    stones.captives = malloc( ( 1 + stoneCount ) * sizeof( int ) );
    assert( stones.captives && "Bad malloc" );

    return stones;
}

void initStones(
    Stones* stones,
    int const playerCount,
    int const stoneCountPerPlayer
)
{
    int playerId = 1;
    int idx = 0;

    stones->affiliations[idx] = 0;
    stones->captives[idx] = 0;

    for ( int n = 0; n < playerCount; ++n )
    {
        for ( int m = 0; m < stoneCountPerPlayer; ++m )
        {
            ++idx;

            stones->affiliations[idx] = playerId;
            stones->captives[idx] = 0;
        }
        ++playerId;
    }

    assert( stones->affiliations[0] == 0 && "StoneId 0 is unassigned" );
    assert( stones->captives[0] == 0 && "StoneId 0 is unassigned" );
    assert( stones->affiliations[1] == 1 );
    assert( stones->affiliations[stoneCountPerPlayer] == 1 );
    assert( stones->affiliations[stoneCountPerPlayer + 1] == 2 );
    assert( stones->affiliations[2 * stoneCountPerPlayer] == 2 );
}

void deinitStones( Stones* const stones )
{
    free( stones->affiliations );
    free( stones->captives );
}
