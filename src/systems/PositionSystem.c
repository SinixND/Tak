#include "PositionSystem.h"

#include "FileId.h"
#include "RankId.h"
#include <assert.h>

int positionToBoardIndex(
    FileId const file,
    RankId const rank,
    int const boardWidth
)
{
    assert(
        ( boardWidth > 0 )
        && "Invalid boardWidth"
    );

    return ( rank * boardWidth ) + file;
}
