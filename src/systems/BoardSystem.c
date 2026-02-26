#include "BoardSystem.h"

#include "Board.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "StoneType.h"
#include <assert.h>

Board newBoard( void )
{
    Board board = {
        .stacks = { 0 },
        .types = { 0 },
    };

    for ( int stackIdx = 0; stackIdx < STACKS_MAX; ++stackIdx )
    {
        for ( int stoneIdx = 0; stoneIdx < STONES_MAX; ++stoneIdx )
        {
            board.stacks[stackIdx].affiliations[stoneIdx] = PLAYER_NONE;
        }
    }

    return board;
}

Board putStoneOnStack(
    Board board,
    int const stackIdx,
    PlayerId const playerId,
    StoneType const type
)
{
    assert( ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK ) && "PlayerId invalid" );

    //* Stack needs to be empty
    assert(
        board.stacks[stackIdx].height == 0
        && "Can only place on empty tile"
    );

    Stack* const stack = &board.stacks[stackIdx];

    //* Add affiliation
    stack->affiliations[stack->height] = playerId;

    //* Set played stone type
    board.types[stackIdx] = type;

    //* Increase stack height
    ++stack->height;

    return board;
}
