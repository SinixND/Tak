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
        stacks.topStoneIdxs[idx] = -1;
        stacks.heights[idx] = 0;
        stacks.types[idx] = NONE;
    }

    return stacks;
}

void deinitStacks( Stacks* const stacks )
{
    free( stacks->topStoneIdxs );
    free( stacks->heights );
    free( stacks->types );
}

Stacks allocateStackComponents( int const boardSize )
{
    int const stackCount = boardSize * boardSize;

    Stacks stacks = { .onBoardCount = 0 };

    stacks.topStoneIdxs = malloc( stackCount * sizeof( int ) );
    assert( stacks.topStoneIdxs && "Bad malloc" );

    stacks.heights = malloc( stackCount * sizeof( int ) );
    assert( stacks.heights && "Bad malloc" );

    stacks.types = malloc( stackCount * sizeof( StoneType ) );
    assert( stacks.types && "Bad malloc" );

    return stacks;
}
