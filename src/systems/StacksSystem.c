#include "StacksSystem.h"

#include "Stacks.h"
#include "StoneType.h"
#include <assert.h>

Stacks newStacks( void )
{
    Stacks stacks = {
        { NONE },
        { 0 },
        { { 0 } }
    };

    return stacks;
}

Stacks putStoneOnStack(
    Stacks stacks,
    int const stackIdx,
    int const playerIdx,
    StoneType const type
)
{
    assert( ( playerIdx == 1 || playerIdx == 2 ) && "PlayerIdx invalid" );

    //* Add affiliation
    stacks.affiliations[stackIdx][stacks.heights[stackIdx]] = playerIdx;

    //* Set played stone type
    stacks.types[stackIdx] = type;

    //* Increase stack height
    ++stacks.heights[stackIdx];

    return stacks;
}
