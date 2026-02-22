#include "StackSystem.h"

#include "Stacks.h"
#include "StoneType.h"
#include <assert.h>

Stacks newStacks( int const boardWidth )
{
    assert( ( boardWidth >= (int)BOARD_WIDTH_MIN ) && "Board width value too small" );
    assert( ( boardWidth <= (int)BOARD_WIDTH_MAX ) && "Board width value too big" );

    Stacks stacks;

    for ( int i = 0; i < STACKS_ARRAY_SIZE; ++i )
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

Stacks putStoneOnStack(
    Stacks stacks,
    int const stackIdx,
    StoneType const type
)
{
    //* Set played stone type
    stacks.types[stackIdx] = type;

    //* Increase stack height
    ++stacks.heights[stackIdx];

    return stacks;
}
