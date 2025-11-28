#include "StackSystem.h"

#include "Stacks.h"
#include "StoneType.h"
#include <assert.h>
#include <stdlib.h>

Stacks allocateStackComponents( int const stackCount )
{
    Stacks stacks;

    stacks.topStoneIds = malloc( stackCount * sizeof( int ) );
    assert( stacks.topStoneIds && "Bad malloc" );

    stacks.heights = malloc( stackCount * sizeof( int ) );
    assert( stacks.heights && "Bad malloc" );

    stacks.types = malloc( stackCount * sizeof( StoneType ) );
    assert( stacks.types && "Bad malloc" );

    return stacks;
}

void initStacks(
    Stacks* stacks,
    int const boardSize
)
{
    for ( int idx = 0; idx < boardSize; ++idx )
    {
        stacks->heights[idx] = 0;
        stacks->topStoneIds[idx] = 0;
        stacks->types[idx] = NONE;
    }
}

void deinitStacks( Stacks* const stacks )
{
    free( stacks->heights );
    free( stacks->topStoneIds );
    free( stacks->types );
}
