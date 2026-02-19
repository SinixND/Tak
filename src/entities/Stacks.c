#include "Stacks.h"

#include "StoneType.h"
#include <assert.h>
#include <stdlib.h>

/// Allocate memory
Stacks allocateStackComponents( int const stackCount );

Stacks initStacks( int const boardWidth )
{
    int const tileCount = boardWidth * boardWidth;

    Stacks stacks = allocateStackComponents( tileCount );

    for ( int idx = 0; idx < tileCount; ++idx )
    {
        stacks.boardIdxs[idx] = -1;
        stacks.topStoneIdxs[idx] = -1;
        stacks.heights[idx] = 0;
        stacks.types[idx] = NONE;
    }

    return stacks;
}

void deinitStacks( Stacks* const stacks )
{
    free( stacks->boardIdxs );
    free( stacks->topStoneIdxs );
    free( stacks->heights );
    free( stacks->types );
}

Stacks allocateStackComponents( int const stackCount )
{
    assert(
        stackCount > 0
        && "Invalid stackCount"
    );

    Stacks stacks = { .onBoardCount = 0 };

    stacks.boardIdxs = calloc( stackCount, sizeof( int ) );
    assert( stacks.boardIdxs && "Bad allocation" );

    stacks.topStoneIdxs = calloc( stackCount, sizeof( int ) );
    assert( stacks.topStoneIdxs && "Bad allocation" );

    stacks.heights = calloc( stackCount, sizeof( int ) );
    assert( stacks.heights && "Bad allocation" );

    stacks.types = calloc( stackCount, sizeof( StoneType ) );
    assert( stacks.types && "Bad allocation" );

    return stacks;
}
