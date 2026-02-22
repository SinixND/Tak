#include "Stacks.h"

#include "GameConstants.h"
#include "StoneType.h"
#include <assert.h>

/// Set default values for Stacks
Stacks initStacks( int const boardWidth )
{
    Stacks stacks;

    assert( ( boardWidth >= (int)BOARD_WIDTH_MIN ) && "Board width value too small" );
    assert( ( boardWidth <= (int)BOARD_WIDTH_MAX ) && "Board width value too big" );

    for ( int i = 0; i < STACKS_MAX; ++i )
    {
        stacks.types[i] = NONE;
        stacks.heights[i] = 0;
        for ( int j = 0; j < STONES_MAX; ++j )
        {
            stacks.stones[i][j] = 0;
        }
    }

    return stacks;
}

