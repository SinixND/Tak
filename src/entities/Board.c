#include "Board.h"

#include <assert.h>
#include <stdlib.h>

/// Allocate memory
Board allocateBoardComponents( int const boardSize );

Board initBoard( int const boardSize )
{
    Board board = allocateBoardComponents( boardSize );

    int const stackCount = boardSize * boardSize;

    for ( int idx = 0; idx < stackCount; ++idx )
    {
        board.stackIdxs[idx] = -1;
    }

    return board;
}

void deinitBoard( Board* const board )
{
    free( board->stackIdxs );
}

Board allocateBoardComponents( int const boardSize )
{
    int const stackCount = boardSize * boardSize;

    Board board = { .size = boardSize };

    board.stackIdxs = malloc( stackCount * sizeof( int ) );
    assert( board.stackIdxs && "Bad malloc" );

    return board;
}
