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
        ( boardSize >= BOARD_SIZE_MIN )
        && ( boardSize <= BOARD_SIZE_MAX )
        && "Board size invalid"
    );

    assert(
        ( fileX >= 0 )
        && ( fileX < boardSize )
        && ( rankY >= 0 )
        && ( rankY < boardSize )
        && "Position invalid"
    );

    return ( rankY * boardSize ) + fileX;
}

int squareToStackIndex(
    int const squareIdx,
    int const boardSize
)
{
    assert(
        ( boardSize >= BOARD_SIZE_MIN )
        && ( boardSize <= BOARD_SIZE_MAX )
        && "Board size invalid"
    );

    assert(
        ( squareIdx >= 0 )
        && ( squareIdx < ( boardSize * boardSize ) )
        && "Square index invalid"
    );

    return squareIdx * getStackCapacity( boardSize );
}
