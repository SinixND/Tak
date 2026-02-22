#include "StackSystem.h"

#include "Stacks.h"
#include "StoneType.h"
#include <assert.h>

Stack newStack( int const boardWidth )
{
    assert( ( boardWidth >= (int)BOARD_WIDTH_MIN ) && "Board width value too small" );
    assert( ( boardWidth <= (int)BOARD_WIDTH_MAX ) && "Board width value too big" );

    Stack stack;

    stack.type = NONE;
    stack.height = 0;

    for ( int i = 0; i < STONES_MAX; ++i )
    {
        stack.affiliations[i] = 0;
    }

    return stack;
}

