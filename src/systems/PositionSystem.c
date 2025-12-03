#include "PositionSystem.h"

int positionToBoardIndex(
    int const x,
    int const y,
    int const boardSize
)
{
    return ( y * boardSize ) + x;
}
