#include "BoardSystem.h"

#include "Board.h"
#include "StackSystem.h"
#include "StoneType.h"
#include <assert.h>

Board newBoard( void )
{
    Board board = {
        .stacks = { 0 },
        .types = { 0 },
    };

    return board;
}

Board putStoneOnStack(
    Board board,
    int const stackIdx,
    PlayerId const playerId,
    StoneType const type
)
{
    assert( ( playerId == 1 || playerId == 2 ) && "PlayerIdx invalid" );

    //* Add affiliation
    int* const pHeight = &board.stacks[stackIdx].height;

    board.stacks[stackIdx].affiliations[*pHeight] = playerId;

    //* Set played stone type
    board.types[stackIdx] = type;

    //* Increase stack height
    ++( *pHeight );
    ;

    return board;
}
