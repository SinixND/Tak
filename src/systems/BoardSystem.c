#include "BoardSystem.h"

#include "Board.h"
#include <assert.h>
#include <stdlib.h>

Board allocateBoardComponents( int const boardSize )
{
    Board board;

    board.stacks = malloc( ( boardSize * boardSize ) * sizeof( int ) );
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
}

void deinitBoard( Board* const board )
{
    free( board->stacks );
}
