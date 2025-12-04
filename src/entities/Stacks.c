#include "Stacks.h"

#include "StoneType.h"
#include <assert.h>
#include <stdlib.h>

/// Allocate memory
Stacks allocateStackComponents( int const boardSize );

Stacks initStacks( int const boardSize )
{
    int const stackCount = boardSize * boardSize;

    Stacks stacks = allocateStackComponents( boardSize );

    for ( int idx = 0; idx < stackCount; ++idx )
    {
        stacks.topStoneIds[idx] = -1;
        stacks.heights[idx] = 0;
        stacks.types[idx] = NONE;
    }

    return stacks;
}

void deinitStacks( Stacks* const stacks )
{
    free( stacks->topStoneIds );
    free( stacks->heights );
    free( stacks->types );
}

Stacks allocateStackComponents( int const boardSize )
{
    int const stackCount = boardSize * boardSize;

    Stacks stacks = { .onBoard = 0 };

    stacks.topStoneIds = malloc( stackCount * sizeof( int ) );
    assert( stacks.topStoneIds && "Bad malloc" );

    stacks.heights = malloc( stackCount * sizeof( int ) );
    assert( stacks.heights && "Bad malloc" );

    stacks.types = malloc( stackCount * sizeof( StoneType ) );
    assert( stacks.types && "Bad malloc" );

    return stacks;
}
