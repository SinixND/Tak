#include "Board.h"

#include <assert.h>
#include <stdlib.h>

/// Allocate memory
Board allocateBoardComponents( int const boardWidth );

Board initBoard( int const boardWidth )
{
    Board board = allocateBoardComponents( boardWidth );

    int const tileCount = boardWidth * boardWidth;

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

Board allocateBoardComponents( int const boardWidth )
{
    assert(
        boardWidth > 0
        && "Invalid boardWidth"
    );

    Board board = { .width = boardWidth };

    int const tileCount = boardWidth * boardWidth;

    board.stackIdxs = calloc( tileCount, sizeof( int ) );
    assert( board.stackIdxs && "Bad allocation" );

    return board;
}
