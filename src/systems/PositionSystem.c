#include "PositionSystem.h"

#include "ColumnId.h"
#include "RowId.h"
#include <assert.h>

int positionToBoardIndex(
    ColumnId const column,
    RowId const row,
    BoardWidthId const boardWidthId
)
{
    assert(
        ( boardWidthId > 0 )
        && "Invalid boardWidthId"
    );

    return ( row * boardWidthId ) + column;
}
