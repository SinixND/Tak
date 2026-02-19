#include "PositionSystem.h"
#include <assert.h>

int positionToBoardIndex(
    int const x,
    int const y,
    int const boardWidth
)
{
    assert(
        ( x >= 0 )
        && "Invalid position"
    );

    assert(
        ( y >= 0 )
        && "Invalid position"
    );

    assert(
        ( x < boardWidth )
        && "Invalid position"
    );

    assert(
        ( y < boardWidth )
        && "Invalid position"
    );

    assert(
        ( boardWidth > 0 )
        && "Invalid boardWidth"
    );

    return ( y * boardWidth ) + x;
}
