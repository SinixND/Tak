#include "PositionSystem.h"

#include "FileId.h"
#include "RankId.h"
#include <assert.h>

int positionToStackIndex(
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
