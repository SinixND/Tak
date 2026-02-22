#include "Stack.h"
#include "StoneType.h"

#include <assert.h>

/// Set default values for Stack
Stack initStack( int const boardWidth )
{
    Stack stack;

    assert( ( boardWidth >= (int)BOARD_WIDTH_MIN ) && "Board width value too small" );
    assert( ( boardWidth <= (int)BOARD_WIDTH_MAX ) && "Board width value too big" );

    stack.type = NONE;
    stack.height = 0;

    for ( int i = 0; i < STONES_MAX; ++i )
    {
        stack.affiliations[i] = 0;
    }

    return stack;
}
