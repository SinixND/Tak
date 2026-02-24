#include "BoardSystem.h"

#include "Board.h"
#include "StoneType.h"
#include <assert.h>

Board newBoard( void )
{
    Board board = {
        { NO_STONE },
        { 0 },
        { { 0 } }
    };

    return board;
}

Board putStoneOnStack(
    Board board,
    int const stackIdx,
    int const playerIdx,
    StoneType const type
)
{
    assert( ( playerIdx == 1 || playerIdx == 2 ) && "PlayerIdx invalid" );

    //* Add affiliation
    board.stacks[stackIdx][board.heights[stackIdx]] = playerIdx;

    //* Set played stone type
    board.types[stackIdx] = type;

    //* Increase stack height
    ++board.heights[stackIdx];

    return board;
}
