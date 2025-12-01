#include "Board.h"

#include <assert.h>
#include <stdlib.h>

Board allocateBoardComponents( int const boardSize )
{
    int const stackCount = boardSize * boardSize;
    Board board;

    board.stacks = malloc( stackCount * sizeof( int ) );
    assert( board.stacks && "Bad malloc" );

    return board;
}

void initBoard(
    Board* board,
    int const boardSize
)
{
    int const stackCount = boardSize * boardSize;

    for ( int idx = 0; idx < stackCount; ++idx )
    {
        board->stacks[idx] = 0;
    }

    assert( 
        board->stacks[0] == 0 
        && board->stacks[stackCount - 1] == 0 
        && "Board/stacks array size is at least boardSize^2" 
    );
}

void deinitBoard( Board* const board )
{
    free( board->stacks );
}
