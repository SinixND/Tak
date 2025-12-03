#include "Stacks.h"

#include "StoneType.h"
#include <assert.h>
#include <stdlib.h>

/// Allocate memory; Add one extra to enable invalid ID = 0
Stacks allocateStackComponents( int const boardSize );

Stacks initStacks( int const boardSize )
{
    Stacks stacks = allocateStackComponents( boardSize );

    int const maxIdx = boardSize + 1;

    for ( int idx = 0; idx < maxIdx; ++idx )
    {
        stacks.topStoneIds[idx] = 0;
        stacks.heights[idx] = 0;
        stacks.types[idx] = NONE;
    }

    assert(
        stacks.topStoneIds[0] == 0
        && stacks.heights[0] == 0
        && stacks.types[0] == NONE
        && "Default stack values are 0 or NONE"
    );

    assert(
        stacks.topStoneIds[boardSize] == 0
        && stacks.heights[boardSize] == 0
        && stacks.types[boardSize] == NONE
        && "Stack array sizes are at least (boardSize + 1)"
    );

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
    int const maxIdx = boardSize + 1;

    Stacks stacks = { .onBoard = 0 };

    stacks.topStoneIds = malloc( maxIdx * sizeof( int ) );
    assert( stacks.topStoneIds && "Bad malloc" );

    stacks.heights = malloc( maxIdx * sizeof( int ) );
    assert( stacks.heights && "Bad malloc" );

    stacks.types = malloc( maxIdx * sizeof( StoneType ) );
    assert( stacks.types && "Bad malloc" );

    return stacks;
}
