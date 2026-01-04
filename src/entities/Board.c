#include "Board.h"

#include <assert.h>
#include <stdlib.h>

/// Allocate memory
Board allocateBoardComponents( int const tileCount );

Board initBoard( int const boardWidth )
{
    int const tileCount = boardWidth * boardWidth;

    Board board = allocateBoardComponents( tileCount );

    for ( int idx = 0; idx < tileCount; ++idx )
    {
        board.stackIdxs[idx] = -1;
    }

    return board;
}

void deinitBoard( Board* const board )
{
    free( board->stackIdxs );
}

Board allocateBoardComponents( int const tileCount )
{
    Board board = { .tileCount = tileCount };

    board.stackIdxs = malloc( tileCount * sizeof( int ) );
    assert( board.stackIdxs && "Bad malloc" );

    return board;
}
