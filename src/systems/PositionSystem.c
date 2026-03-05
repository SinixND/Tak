#include "PositionSystem.h"

#include "FileId.h"
#include "RankId.h"
#include <assert.h>

/// Returns index of first stone of stack
int positionToStackIndex(
    FileId const fileX,
    RankId const rankY,
    int const boardWidth,
    int const stackCapacity
);

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

int positionToStackIndex(
    FileId const fileX,
    RankId const rankY,
    int const boardWidth,
    int const stackCapacity
)
{
    assert(
        ( stackCapacity > 0 )
        && "Invalid stone count"
    );

    return positionToSquare(
               fileX,
               rankY,
               boardWidth
           )
           * stackCapacity;
}

int squareToStackIndex(
    int const squareIdx,
    int const stackCapacity
)
{
    assert(
        ( squareIdx >= 0 )
        && "Invalid square value"
    );

    return squareIdx * stackCapacity;
}
