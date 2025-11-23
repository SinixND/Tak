#include "StoneSystem.h"

#include "Stones.h"
#include "RulesData.h"
#include <assert.h>
#include <stdlib.h>

Stones allocateStoneComponents(
    int const playerCount,
    int const stoneCountPerPlayer
)
{
    int const totalStoneCount = (playerCount * stoneCountPerPlayer);

    Stones stones;

    stones.affiliations = malloc( (1 + totalStoneCount) * sizeof( int ) );
    stones.captives = malloc( (1 + totalStoneCount) * sizeof( int ) );

    return stones;
}

void initStones(
    Stones* stones,
    int const playerCount,
    int const stoneCountPerPlayer
)
{
    int idx = 1;

    stones.affiliations[0]= 0;
    stones.captives[0] = 0;

    for ( int i = 0; i < stoneCountPerPlayer; ++i )
    {
        stones.affiliations[idx] = 1;
        stones.captives[idx] = 0;

        ++idx;
    }

    for ( int i = 0; i < stoneCountPerPlayer; ++i )
    {
        stones.affiliations[idx] = 2;
        stones.captives[idx] = 0;

        ++idx;
    }

    assert( stones.affiliations[0] == 0 && "StoneId 0 is unassigned" );
    assert( stones.captives[0] == 0 && "StoneId 0 is unassigned" );
    assert( stones.affiliations[1] == 1 );
    assert( stones.affiliations[stoneCountPerPlayer] == 1 );
    assert( stones.affiliations[stoneCountPerPlayer + 1] == 2 );
    assert( stones.affiliations[ 2 * stoneCountPerPlayer ] == 2 );
}

void deinitStones( Stones* const stones )
{
    free( stones->affiliations );
    free( stones->captives );
}