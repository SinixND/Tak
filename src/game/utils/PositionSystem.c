#include "PositionSystem.h"

#include "FileId.h"
#include "GameConstants.h"
#include "RankId.h"
#include <assert.h>

int positionToSquare(
    FileId const fileX,
    RankId const rankY,
    int const boardSize
)
{
    assert(
        ( boardSize > 2 )
        && "Invalid boardSize"
    );

    assert(
        ( boardSize < 9 )
        && "Invalid boardSize"
    );

    return ( rankY * boardSize ) + fileX;
}

int squareToStackIndex(
    int const squareIdx,
    int const boardSize
)
{
    assert(
        ( boardSize > 2 )
        && "Invalid boardSize"
    );

    assert(
        ( boardSize < 9 )
        && "Invalid boardSize"
    );

    return squareIdx * getStackCapacity( boardSize );
}
