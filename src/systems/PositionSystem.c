#include "PositionSystem.h"

#include "FileId.h"
#include "RankId.h"
#include <assert.h>

int positionToSquare(
    FileId const fileX,
    RankId const rankY,
    int const boardWidth
)
{
    assert(
        ( boardWidth > 0 )
        && "Invalid boardWidth"
    );

    return ( rankY * boardWidth ) + fileX;
}

int squareToStackIndex(
    int const squareIdx,
    int const stackCapacity
)
{
    assert(
        ( squareIdx >= 0 )
        && "Invalid squareIdx"
    );

    return squareIdx * stackCapacity;
}
