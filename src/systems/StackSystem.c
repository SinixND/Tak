#include "StackSystem.h"
#include "Stacks.h"
#include "StoneType.h"
#include "Stones.h"

int getStackIdx(
    int* const boardStackIdxs,
    int* const stacksOnBoardCount,
    int const position
)
{
    //* Get stack index to use
    int stackIdx = boardStackIdxs[position];

    //* If stack is not on the board yet
    if ( stackIdx < 0 )
    {
        //* Get next stack
        stackIdx = ( *stacksOnBoardCount )++;
        //* Add new stack to board
        boardStackIdxs[position] = stackIdx;
    }

    return stackIdx;
}

void putStoneOnStack(
    Stones* const stones,
    Stacks* const stacks,
    int const stoneIdx,
    int const stackIdx,
    StoneType const type
)
{
    //* Add current topStone as captive to new stone
    stones->captiveIdxs[stoneIdx] = stacks->topStoneIdxs[stackIdx];

    //* Set new stone as topStone to stack
    stacks->topStoneIdxs[stackIdx] = stoneIdx;
    //* Set played stone type
    stacks->types[stackIdx] = type;
    //* Increase stack height
    ++stacks->heights[stackIdx];
}
