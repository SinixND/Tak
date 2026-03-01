#include "PositionSystem.h"

#include "FileId.h"
#include "RankId.h"
#include <assert.h>

int positionToBoardIndex(
    FileId const column,
    RankId const row,
    BoardWidthId const boardWidthId
)
{
    assert(
        ( boardWidthId > 0 )
        && "Invalid boardWidthId"
    );

    return ( row * boardWidthId ) + column;
}
