#include "StacksSystem.h"

#include "Stacks.h"
#include "StoneType.h"
#include <assert.h>

Stacks newStacks( int const boardWidth )
{
    assert( ( boardWidth >= (int)BOARD_WIDTH_MIN ) && "Board width value too small" );
    assert( ( boardWidth <= (int)BOARD_WIDTH_MAX ) && "Board width value too big" );

    Stacks stacks;

    for ( int stackIdx = 0; stackIdx < STACKS_ARRAY_SIZE; ++stackIdx )
    {
        stacks.types[stackIdx] = NONE;
        stacks.heights[stackIdx] = 0;

        for ( int stoneIdx = 0; stoneIdx < STONES_MAX; ++stoneIdx )
        {
            stacks.affiliations[stackIdx][stoneIdx] = 0;
        }
    }

    return stacks;
}

Stacks putStoneOnStack(
    Stacks stacks,
    int const stackIdx,
    int const playerIdx,
    StoneType const type
)
{
    assert( playerIdx >= 1 && "PlayerIdx invalid" );
    assert( playerIdx <= 2 && "PlayerIdx invalid" );

    //* Add affiliation
    stacks.affiliations[stackIdx][stacks.heights[stackIdx]] = playerIdx;

    //* Set played stone type
    stacks.types[stackIdx] = type;

    //* Increase stack height
    ++stacks.heights[stackIdx];

    return stacks;
}
