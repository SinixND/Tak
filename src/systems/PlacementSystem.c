#include "PlacementSystem.h"

#include "Board.h"
#include "Players.h"
#include "Stacks.h"
#include "StoneType.h"
#include "Stones.h"
#include <assert.h>

void placeStone(
    Players* players,
    Board* board,
    Stacks* stacks,
    Stones* stones,
    int const player,
    int const positionX,
    int const positionY,
    StoneType const type
)
{
    //* Get position value
    int const position = ( positionY * board->size ) + positionX;
    //* Get stack index to use
    int stackIdx = board->stackIdxs[position];

    //* Can it be placed?
    assert( ( stacks->types[stackIdx] != CAP ) && "[ERROR] Cant place stones on top of capstone" );
    assert( !( ( stacks->types[stackIdx] == WALL ) && ( type != CAP ) ) && "[ERROR] Only capstone can be played on walls" );

    //* If stack is not on the board yet
    if ( stackIdx < 0 )
    {
        //* Get next stack
        stackIdx = stacks->onBoardCount++;
        //* Add new stack to board
        board->stackIdxs[position] = stackIdx;
    }

    //* Adjust player reserves
    switch ( type )
    {
        case FLAT:
        case WALL:
        {
            --players->regularReserves[player];
            break;
        }

        case CAP:
        {
            --players->capstoneReserves[player];
            break;
        }
        default:
        {
            break;
        }
    }

    //* Get new stone index
    int const stoneIdx = stones->inPlayCount++;

    //* Add current topStone as captive to new stone
    stones->captiveIdxs[stoneIdx] = stacks->topStoneIdxs[stackIdx];

    //* Set new stone as topStone to stack
    stacks->topStoneIdxs[stackIdx] = stoneIdx;
    //* Set played stone type
    stacks->types[stackIdx] = type;
    //* Increase stack height
    ++stacks->heights[stackIdx];
}
