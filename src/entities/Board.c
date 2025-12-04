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
        board.stacks[idx] = 0;
    }

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

