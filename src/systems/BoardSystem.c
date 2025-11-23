#include "BoardSystem.h"

/// Allocates empty board
#include <assert.h>
#include <stdlib.h>

Stack* initBoard( int boardSize )
{
    Stack* board = malloc( ( boardSize * boardSize ) * sizeof( Stack ) );
    assert( board && "Bad malloc" );

    for ( int idx = 0; idx < boardSize; ++idx )
    {
        board[idx].height = 0;
        board[idx].topStone = 0;
    }

    assert( board[0].height == 0 );
    assert( board[boardSize].topStone == 0 );

    return board;
}
