#include "StackSystem.h"
#include "Stacks.h"
#include "StoneType.h"
#include "Stones.h"
#include <assert.h>

int createOrGetStackIdx(
    int* const boardStackIdxs,
    int* const stacksOnBoardCount,
    int* const stackBoardIdxs,
    int const boardIdx
)
{
    //* Get stack index to use
    int stackIdx = boardStackIdxs[boardIdx];

    //* If stack is not on the board yet
    if ( stackIdx < 0 )
    {
        //* Get next stack
        stackIdx = ( *stacksOnBoardCount )++;
        //* Store board index
        stackBoardIdxs[stackIdx] = boardIdx;
        //* Add new stack to board
        boardStackIdxs[boardIdx] = stackIdx;
    }

    return stackIdx;
}
