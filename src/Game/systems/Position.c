#include "Position.h"

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
        ( fileX >= 0 )
        && ( fileX < 8 )
        && "Invalid fileX"
    );

    assert(
        ( rankY >= 0 )
        && ( rankY < 8 )
        && "Invalid rankY"
    );

    assert(
        ( boardSize > 2 )
        && "BoardSize too small"
    );

    assert(
        ( boardSize < 9 )
        && "BoardSize too big"
    );

    return ( rankY * boardSize ) + fileX;
}

int squareToStackIndex(
    int const squareIdx,
    int const boardSize
)
{
    assert(
        ( squareIdx >= 0 )
        && ( squareIdx < ( BOARD_SIZE_MAX * BOARD_SIZE_MAX ) )
        && "Invalid square index"
    );

    assert(
        ( boardSize > 2 )
        && "BoardSize too small"
    );

    assert(
        ( boardSize < 9 )
        && "BoardSize too big"
    );

    return squareIdx * getStackCapacity( boardSize );
}
