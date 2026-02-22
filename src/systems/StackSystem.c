#include "StackSystem.h"

#include "StoneType.h"
#include <assert.h>

Stack newStack( int const boardWidth )
{
    assert( ( boardWidth >= (int)BOARD_WIDTH_MIN ) && "Board width value too small" );
    assert( ( boardWidth <= (int)BOARD_WIDTH_MAX ) && "Board width value too big" );

    Stack stack;

    stack.type = NONE;
    stack.height = 0;

    for ( int stoneIdx = 0; stoneIdx < STONES_MAX; ++stoneIdx )
    {
        stack.affiliations[stoneIdx] = 0;
    }

    return stack;
}

