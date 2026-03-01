#include "PositionSystem.h"

#include "FileId.h"
#include "RankId.h"
#include <assert.h>

int positionToBoardIndex(
    FileId const file,
    RankId const rank,
    BoardWidthId const boardWidthId
)
{
    assert(
        ( boardWidthId > 0 )
        && "Invalid boardWidthId"
    );

    return ( rank * boardWidthId ) + file;
}
