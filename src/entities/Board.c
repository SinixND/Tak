#include "Board.h"

#include <assert.h>
#include <stdlib.h>

/// Allocate memory; Add one extra to enable invalid ID = 0
Board allocateBoardComponents( int const boardSize );

Board initBoard( int const boardSize )
{
    Board board = allocateBoardComponents( boardSize );

    int const stackCount = boardSize * boardSize;

    for ( int idx = 0; idx < stackCount; ++idx )
    {
        board.stacks[idx] = 0;
    }

    assert(
        board.stacks[0] == 0
        && board.stacks[stackCount - 1] == 0
        && "Board/stacks array size is at least boardSize^2"
    );

    return board;
}

void deinitBoard( Board* const board )
{
    free( board->stacks );
}

Board allocateBoardComponents( int const boardSize )
{
    int const stackCount = boardSize * boardSize;
    Board board = { .size = boardSize };

    board.stacks = malloc( stackCount * sizeof( int ) );
    assert( board.stacks && "Bad malloc" );

    return board;
}
