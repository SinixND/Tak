#include "BoardSystem.h"

#include "Board.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "StackSystem.h"
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
        board.stacks[stackIdx] = newStack();
    }

    return board;
}

Board addStoneToBoard(
    Board board,
    int const stackIdx,
    PlayerId const playerId,
    StoneType const stoneType
)
{
    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    assert(
        stoneType != STONE_TYPE_NONE
        && "Invalid stoneType"
    );

    board.types[stackIdx] = stoneType;

    board.stacks[stackIdx] = addStoneToStack(
        board.stacks[stackIdx],
        playerId
    );

    return board;
}
