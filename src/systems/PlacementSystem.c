#include "PlacementSystem.h"

#include "Board.h"
#include "Players.h"
#include "PositionSystem.h"
#include "ReserveSystem.h"
#include "StackSystem.h"
#include "Stacks.h"
#include "StoneType.h"
#include "Stones.h"
#include <assert.h>

void placeStoneOnBoard(
    Players* const players,
    Board* const board,
    Stacks* const stacks,
    Stones* const stones,
    int const player,
    int const positionX,
    int const positionY,
    StoneType const type
)
{
    int const stackIdx = getStackIdx(
        board->stackIdxs,
        &stacks->onBoardCount,
        positionToBoardIndex(
            positionX,
            positionY,
            board->size
        )
    );

    //* Can it be placed?
    assert(
        ( stacks->types[stackIdx] != CAP )
        && !( ( type != CAP ) && ( stacks->types[stackIdx] == WALL ) )
        && "Cant place stone"
    );

    int const stoneIdx = takeFromReserves(
        players->regularReserves,
        players->capstoneReserves,
        &stones->inPlayCount,
        player,
        type
    );

    putStoneOnStack(
        stones,
        stacks,
        stoneIdx,
        stackIdx,
        type
    );
}
