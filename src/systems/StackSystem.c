#include "StackSystem.h"

#include "Stacks.h"
#include "StoneType.h"
#include <assert.h>

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
